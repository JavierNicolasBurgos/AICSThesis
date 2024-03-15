// Fill out your copyright notice in the Description page of Project Settings.


#include "StateMachineAIController.h"
#include "GameFramework/Character.h"
#include "NavigationSystem.h"
#include "Tasks/AITask_MoveTo.h"

void AStateMachineAIController::OnPossess(APawn* InPawn)
{
	CurrentStateMachine = EAIStateMachines::Patrol;
	Super::OnPossess(InPawn);
}

void AStateMachineAIController::BeginPlay()
{
	Super::BeginPlay();
	GetRandomPointAndTryingToMoveAI();
}

void AStateMachineAIController::GetRandomPointAndTryingToMoveAI()
{
	FVector NewAIDestination;
	GetRandomPoint(NewAIDestination);
	TryingToMoveAI(NewAIDestination);
}

void AStateMachineAIController::GetRandomPoint(FVector& DestinationToMove) const
{
	const UNavigationSystemV1* NavSys = UNavigationSystemV1::GetCurrent(GetWorld());

	FNavLocation NavLocation;
	const bool bCanGetRandomPoint = NavSys->GetRandomPointInNavigableRadius(GetCharacter()->GetActorLocation(), RandomPointRadius, NavLocation);
	bCanGetRandomPoint ? DestinationToMove = NavLocation.Location : DestinationToMove = FAISystem::InvalidLocation;
}

void AStateMachineAIController::TryingToMoveAI(const FVector& AIDestination)
{
	FAIMoveRequest MoveRequest;

	if (FAISystem::IsValidLocation(AIDestination))
	{
		MoveRequest.SetGoalLocation(AIDestination);
	}

	MoveRequest.SetNavigationFilter(GetDefaultNavigationFilterClass());

	UAITask_MoveTo* MyTask = UAITask::NewAITask<UAITask_MoveTo>(*this, EAITaskPriority::High);
	check(MyTask);
	MyTask->SetUp(this, MoveRequest);
	MyTask->ReadyForActivation();
}

void AStateMachineAIController::OnMoveCompleted(FAIRequestID RequestID, const FPathFollowingResult& Result)
{
	Super::OnMoveCompleted(RequestID, Result);

	if (Result.Flags == FPathFollowingResultFlags::Success)
	{
		ResumeRandomMovementAfterWaitTime();
	}
	else
	{
		GetRandomPointAndTryingToMoveAI();
	}
}

void AStateMachineAIController::ResumeRandomMovementAfterWaitTime()
{
	StopMovement();
	const float RemainingWaitTime = FMath::FRandRange(FMath::Max(0.0f, WaitTime - WaitTimeRandomDeviation), (WaitTime + WaitTimeRandomDeviation));
	GetWorldTimerManager().SetTimer(WaitTimerHandle, this, &AStateMachineAIController::GetRandomPointAndTryingToMoveAI, RemainingWaitTime, false);
}






