// Fill out your copyright notice in the Description page of Project Settings.


#include "BTTask_GenerateRandomPoint.h"
#include "AIController.h"
#include "GameFramework/Character.h"
#include "NavigationSystem.h"
#include "AIOverviewThesis/AIHelpers/AIHelpersLibrary.h"
#include "BehaviorTree/BlackboardComponent.h"



UBTTask_GenerateRandomPoint::UBTTask_GenerateRandomPoint(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer)
{
	NodeName = "Generate a Random Point";
}

EBTNodeResult::Type UBTTask_GenerateRandomPoint::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	EBTNodeResult::Type BTTaskResult = Super::ExecuteTask(OwnerComp, NodeMemory);

	const UNavigationSystemV1* NavSys = UNavigationSystemV1::GetCurrent(GetWorld());
	FNavLocation NavLocation;
	const bool bCanGetRandomPoint = NavSys->GetRandomPointInNavigableRadius(OwnerComp.GetAIOwner()->GetCharacter()->GetActorLocation(), RandomPointRadius, NavLocation);

	if (bCanGetRandomPoint)
	{
		OwnerComp.GetBlackboardComponent()->SetValueAsVector(UAIHelpersLibrary::GetTargetLocationName(), NavLocation.Location);
		BTTaskResult = EBTNodeResult::Succeeded;
	}
	else
	{
		OwnerComp.GetBlackboardComponent()->SetValueAsVector(UAIHelpersLibrary::GetTargetLocationName(), FAISystem::InvalidLocation);
		BTTaskResult = EBTNodeResult::Failed;
	}

	return BTTaskResult;
}

FString UBTTask_GenerateRandomPoint::GetStaticDescription() const
{
	return FString::Printf(TEXT("%s in: %.1f unit radius of the IA."), *Super::GetStaticDescription(), RandomPointRadius);
}
