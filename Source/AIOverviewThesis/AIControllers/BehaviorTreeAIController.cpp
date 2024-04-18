// Fill out your copyright notice in the Description page of Project Settings.


#include "BehaviorTreeAIController.h"
#include "AIOverviewThesis/AIHelpers/AIHelpersLibrary.h"
#include "BehaviorTree/BlackboardComponent.h"


void ABehaviorTreeAIController::OnPossess(APawn* InPawn)
{
	Super::OnPossess(InPawn);
	RunBehaviorTree(BTToRun);
}

void ABehaviorTreeAIController::PerceptionUpdated(AActor* Actor, FAIStimulus Stimulus)
{
	Super::PerceptionUpdated(Actor, Stimulus);

	GetBlackboardComponent()->SetValueAsVector(UAIHelpersLibrary::GetLastStimulusLocationName(), Stimulus.StimulusLocation);

	if (Stimulus.WasSuccessfullySensed())
	{
		GetBlackboardComponent()->SetValueAsObject(UAIHelpersLibrary::GetTargetActorName(), Actor);
	}
	else
	{
		GetBlackboardComponent()->SetValueAsObject(UAIHelpersLibrary::GetTargetActorName(), nullptr);
	}
}