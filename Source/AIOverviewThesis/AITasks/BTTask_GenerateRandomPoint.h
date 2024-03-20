// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTTaskNode.h"
#include "BTTask_GenerateRandomPoint.generated.h"

/**
 * Represents a behavior tree task node responsible for generating a random point for the AI to move to.
 */
UCLASS()
class AIOVERVIEWTHESIS_API UBTTask_GenerateRandomPoint : public UBTTaskNode
{
	GENERATED_UCLASS_BODY()
	
private:

	UPROPERTY(EditInstanceOnly, Category = "Thesis")
	float RandomPointRadius = 500.0f;
	
protected:

	/*
	* Executes the task of generating a random point for the AI to move to.
	* 
	* @param OwnerComp The behavior tree component that owns this node.
	* @param NodeMemory Pointer to the memory allocated for this node.
	* @return The result of executing the task.
	*/
	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;

	virtual FString GetStaticDescription() const override;
};
