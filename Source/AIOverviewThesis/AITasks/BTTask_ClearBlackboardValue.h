// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTTaskNode.h"
#include "BTTask_ClearBlackboardValue.generated.h"

/**
 * Blackboard task node that clears a specific blackboard value.
 * This task never failed.
 */
UCLASS()
class AIOVERVIEWTHESIS_API UBTTask_ClearBlackboardValue : public UBTTaskNode
{
	GENERATED_BODY()

protected:

	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;

	/** Selector for the blackboard key that will be cleared. */
	UPROPERTY(EditAnywhere, Category="Thesis")
	FBlackboardKeySelector BlackboardKeyToClear;
};
