// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "BehaviorTreeAIController.generated.h"

/**
 * AI controller class that implements a controller for an NPC with Behavior Trees.
 * This class handles the behavior and decisions of the NPC using a Behavior Trees.
 */
UCLASS()
class AIOVERVIEWTHESIS_API ABehaviorTreeAIController : public AAIController
{
	GENERATED_BODY()

private:

	/**
	* The behavior tree asset to run for this AI controller.
	*/
	UPROPERTY(EditDefaultsOnly, Category = "Thesis|AI")
	TObjectPtr<UBehaviorTree> BTToRun;
	
protected:

	
	/**
	* @brief Called when this AI controller "possesses" a pawn (usually a playable character).
	*/
	virtual void OnPossess(APawn* InPawn) override;
};
