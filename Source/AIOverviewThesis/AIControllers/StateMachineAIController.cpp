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

void AStateMachineAIController::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);

	CanSeePlayer();
}

bool AStateMachineAIController::CanSeePlayer() const
{
	const ACharacter* PlayerCharacter = GetWorld()->GetFirstPlayerController()->GetCharacter();

	if (PlayerCharacter)
	{
		const float DistanceToPlayer = CalculateSquaredDistanceToPlayer(PlayerCharacter);
		if (DistanceToPlayer <= LoseSightRadius * LoseSightRadius)
		{
			const float AngleInDegrees = CalculateViewAngleToPlayer(PlayerCharacter);
			const bool bLineOfSightTo = LineOfSightTo(PlayerCharacter);
			if (bLineOfSightTo && AngleInDegrees <= AIFieldOfView)
			{
				// The AI can see the player
				GEngine->AddOnScreenDebugMessage(-1, 0.0f, FColor::Emerald, FString::Printf(TEXT("Can see")));

				return true;
			}	
		}
		
	}

	return false;
}

float AStateMachineAIController::CalculateViewAngleToPlayer(const ACharacter* PlayerCharacter) const
{
	const ACharacter* AICharacter = GetCharacter();

	FVector DirectionVector = PlayerCharacter->GetActorLocation() - AICharacter->GetActorLocation();
	DirectionVector.Normalize();

	const FVector AIForward = AICharacter->GetActorForwardVector();

	float AngleInDegrees = FMath::Acos(FVector::DotProduct(AIForward, DirectionVector));
	AngleInDegrees = FMath::RadiansToDegrees(AngleInDegrees);

	return AngleInDegrees;
}

float AStateMachineAIController::CalculateSquaredDistanceToPlayer(const ACharacter* PlayerCharacter) const
{
	const ACharacter* AICharacter = GetCharacter();
	const FVector DirectionVector = PlayerCharacter->GetActorLocation() - AICharacter->GetActorLocation();
	return DirectionVector.SizeSquared();
}

void AStateMachineAIController::BeginPlay()
{
	Super::BeginPlay();
	GetRandomPointAndTryingToMoveAI();
}

void AStateMachineAIController::GetRandomPointAndTryingToMoveAI()
{
	ClearWaitTimer();
	
	FVector NewAIDestination;
	GetRandomPoint(NewAIDestination);
	TryingToMoveAI(NewAIDestination);
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