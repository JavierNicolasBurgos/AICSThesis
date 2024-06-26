// Fill out your copyright notice in the Description page of Project Settings.


#include "UtilityAIComponent.h"
#include "AIController.h"
#include "AIOverviewThesis/Objects/UtilityAction.h"
#include "AIOverviewThesis/Objects/UtilityConsideration.h"

// Sets default values for this component's properties
UUtilityAIComponent::UUtilityAIComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.

	PrimaryComponentTick.bCanEverTick = true;
}


void UUtilityAIComponent::OnRegister()
{
	Super::OnRegister();
	
	AIController = Cast<AAIController>(GetOwner());
	checkf(AIController, TEXT("This component must be placed on an AIController, otherwise it will not work."));
}

// Called when the game starts
void UUtilityAIComponent::BeginPlay()
{
	Super::BeginPlay();
	
	CreateDefaultActions();

	SetSelectBestActionUpdateType(SelectBestActionUpdateType);
}

void UUtilityAIComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	if (SelectBestActionUpdateType == EUtilityUpdate::Tick)
	{
		SelectBestAction();
	}
}

TArray<UUtilityAction*> UUtilityAIComponent::GetActions() const
{
	return Actions.Array();
}

UUtilityAction* UUtilityAIComponent::GetCurrentAction() const
{
	return CurrentAction;
}

void UUtilityAIComponent::SetSelectBestActionUpdateType(const EUtilityUpdate Value, const float TimerRate)
{
	SelectBestActionUpdateType = Value;
	SelectBestActionTimerRate = TimerRate;

	switch (SelectBestActionUpdateType)
	{
	case EUtilityUpdate::None:

		SetComponentTickEnabled(false);

		if (GetWorld()->GetTimerManager().IsTimerActive(TimerHandle))
		{
			GetWorld()->GetTimerManager().ClearTimer(TimerHandle);
		}
		
		SelectBestAction();

		break;
	case EUtilityUpdate::Tick:

		if (GetWorld()->GetTimerManager().IsTimerActive(TimerHandle))
		{
			GetWorld()->GetTimerManager().ClearTimer(TimerHandle);
		}
		
		SetComponentTickEnabled(true);
		
		break;
	case EUtilityUpdate::Timer:

		SetComponentTickEnabled(false);

		if (!GetWorld()->GetTimerManager().IsTimerActive(TimerHandle))
		{
			GetWorld()->GetTimerManager().SetTimer(TimerHandle, this, &UUtilityAIComponent::SelectBestAction, SelectBestActionTimerRate, true,0);
		}
		break;
	}
}

EUtilityUpdate UUtilityAIComponent::GetSelectBestActionUpdateType() const
{
	return SelectBestActionUpdateType;
}

UUtilityAction* UUtilityAIComponent::GetActionInstanceByClass(TSubclassOf<UUtilityAction> ActionClass) const
{
	for (UUtilityAction* Action : GetActions())
	{
		if (Action->GetClass() == ActionClass)
			return Action;
	}
	return nullptr;
}

bool UUtilityAIComponent::IsSelectingAction() const
{
	return bSelectingAction;
}

void UUtilityAIComponent::CreateDefaultActions()
{
	Actions.Empty();

	for (const auto& ActionType : DefaultActionTypes)
	{
		AddAction(ActionType);
	}
}

void UUtilityAIComponent::SelectBestAction()
{
	bSelectingAction = true;

	float Score = 0;
	UUtilityAction* BestAction = nullptr;

	for (const auto& Action : Actions)
	{
		const float ActionScore = ScoreAction(Action);
		
		//FLogUtilityAI::VisLogString(GetOwner(), "Action: " + Action->GetName() + " Score: " + FString::SanitizeFloat(ActionScore));
		
		if (ActionScore > Score)
		{
			BestAction = Action;
			Score = BestAction->GetScore();
		}
	}

	if (CurrentAction && CurrentAction != BestAction && CurrentAction->IsExecutingAction())
	{
		if (CurrentAction->CanCancelAction())
		{
			CurrentAction->CancelAction();
		}
		else
		{
			bSelectingAction = false;
			return;
		}
	}

	if (BestAction)
	{
		CurrentAction = BestAction;
		
		bSelectingAction = false;
	}
	else if(bRandomActionIfSelectBestActionFails)
	{
		TArray<UUtilityAction*> UtilityActions = Actions.Array();
		if (UtilityActions.Num() > 0)
		{
			CurrentAction = Actions.Array()[FMath::RandRange(0, Actions.Num() - 1)];
			bSelectingAction = false;
		}
		else
		{
			ensureMsgf(false, TEXT("The TSet of Actions is empty, it is required to add actions to select the one with the highest score."));
		}
	}
	else
	{
		bSelectingAction = false;
		return;
	}

	//FLogUtilityAI::VisLogString(GetOwner(),"Current Action: " + CurrentAction->GetName());

	if (OnSelectAction.IsBound())
	{
		OnSelectAction.Broadcast(CurrentAction);
	}

	if (CurrentAction)
	{
		CurrentAction->ExecuteAction();
	}
}

bool UUtilityAIComponent::AddAction(const TSubclassOf<UUtilityAction> ActionType)
{
	if (ActionType)
	{
		for (const auto& Action : Actions)
		{
			if (Action->GetClass() == ActionType)
			{
				return false;
			}
		}

		UUtilityAction* Action = NewObject<UUtilityAction>(AIController, ActionType);
		Actions.Add(Action);
		Action->InitializeVariables(this, AIController);
		Action->CreateConsiderations();
		Action->Construct();

		return true;
	}

	return false;
}

bool UUtilityAIComponent::RemoveAction(const TSubclassOf<UUtilityAction> ActionType)
{
	if (CurrentAction && CurrentAction->GetClass() == ActionType)
	{
		Actions.Remove(CurrentAction);

		SelectBestAction();

		return true;
	}

	for (const auto& Action : Actions)
	{
		if (Action->GetClass() == ActionType)
		{
			Actions.Remove(Action);
			return true;
		}
	}

	return false;
}

float UUtilityAIComponent::ScoreAction(UUtilityAction* Action)
{
	float Score = 1;

	if (Action->Considerations.Num() <= 0)
	{
		return Action->GetScore();
	}

	for (const auto& Consideration : Action->Considerations)
	{
		const float ConsiderationScore = Consideration->EvaluateScore();

		//FLogUtilityAI::VisLogString(GetOwner(), "Action: " + Action->GetName() + " Consideration: " + Consideration->GetName() + " Score: " + FString::SanitizeFloat(ConsiderationScore));
		
		Score *= ConsiderationScore;
		if (Score == 0)
		{
			Action->SetScore(0);
			return Action->GetScore();
		}
	}

	// Averaging scheme of overall score
	const float OriginalScore = Score;
	const float ModFactor = 1 - (1 / Action->Considerations.Num());
	const float MakeupValue = (1 - OriginalScore) * ModFactor;
	Action->SetScore(OriginalScore + (MakeupValue * OriginalScore));

	return Action->GetScore();
}