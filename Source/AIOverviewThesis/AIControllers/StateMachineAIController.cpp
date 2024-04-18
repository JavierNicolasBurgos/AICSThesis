// Fill out your copyright notice in the Description page of Project Settings.


#include "StateMachineAIController.h"
#include "GameFramework/Character.h"
#include "NavigationSystem.h"
#include "Tasks/AITask_MoveTo.h"


void AStateMachineAIController::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);

	if (bCanSeePlayer)
	{
			MoveToActor(GetWorld()->GetFirstPlayerController()->GetCharacter(),AcceptanceRadius);
	}
}

void AStateMachineAIController::BeginPlay()
{
	Super::BeginPlay();
	SetCurrentState(Patrol);
}

void AStateMachineAIController::GetRandomPointAndTryingToMoveAI()
{
	ClearWaitTimer();
	
	FVector NewAIDestination;
	GetRandomPoint(NewAIDestination);
	MoveToLocation(NewAIDestination, AcceptanceRadius);
}

void AStateMachineAIController::ClearWaitTimer()
{
	if (WaitTimerHandle.IsValid())
	{
		GetWorldTimerManager().ClearTimer(WaitTimerHandle);
	}
}

void AStateMachineAIController::GetRandomPoint(FVector& DestinationToMove) const
{
	const UNavigationSystemV1* NavSys = UNavigationSystemV1::GetCurrent(GetWorld());

	FNavLocation NavLocation;
	const bool bCanGetRandomPoint = NavSys->GetRandomPointInNavigableRadius(GetCharacter()->GetActorLocation(), RandomPointRadius, NavLocation);
	bCanGetRandomPoint ? DestinationToMove = NavLocation.Location : DestinationToMove = FAISystem::InvalidLocation;
}

void AStateMachineAIController::OnMoveCompleted(FAIRequestID RequestID, const FPathFollowingResult& Result)
{
	Super::OnMoveCompleted(RequestID, Result);

	if (!bCanSeePlayer)
	{
		SetCurrentState(Patrol);
	}
}

void AStateMachineAIController::ResumeRandomMovementAfterWaitTime()
{
	const float RemainingWaitTime = FMath::FRandRange(FMath::Max(0.0f, WaitTime - WaitTimeRandomDeviation), (WaitTime + WaitTimeRandomDeviation));
	GetWorldTimerManager().SetTimer(WaitTimerHandle, this, &AStateMachineAIController::GetRandomPointAndTryingToMoveAI, RemainingWaitTime, false);
}

void AStateMachineAIController::PerceptionUpdated(AActor* Actor, FAIStimulus Stimulus)
{
	Super::PerceptionUpdated(Actor, Stimulus);
	
	StopMovement();

	LastStimulusLocation = Stimulus.StimulusLocation;

	if (Stimulus.WasSuccessfullySensed())
	{
		bCanSeePlayer = true;

		SetCurrentState(MoveToPlayer);

		GEngine->AddOnScreenDebugMessage(-1, 1.0f, FColor::Emerald, FString::Printf(TEXT("Move To Player state is active.")));
	}
	else
	{
		bCanSeePlayer = false;

		SetCurrentState(MoveToLastStimulusLocation);

		GEngine->AddOnScreenDebugMessage(-1, 1.0f, FColor::Red, FString::Printf(TEXT("Move to last stimulus location state is active")));
	}
}

void AStateMachineAIController::SetCurrentState(EAIStateMachines InState)
{
	CurrentStateMachine = InState;

	switch (CurrentStateMachine)
	{
		case None:
			SetCurrentState(Patrol);
			break;
		case Patrol:
			ResumeRandomMovementAfterWaitTime();
			break;
		case MoveToPlayer:
			MoveToActor(GetWorld()->GetFirstPlayerController()->GetCharacter(), AcceptanceRadius);
			break;
		case MoveToLastStimulusLocation:
			MoveToLocation(LastStimulusLocation, AcceptanceRadius);
			break;
		default:
			break;
	}
}