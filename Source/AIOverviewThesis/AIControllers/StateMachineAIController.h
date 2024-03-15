// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "StateMachineAIController.generated.h"

UENUM()
enum EAIStateMachines
{
	/** State to patrol a given area or route. */
	Patrol = 0,
	/** State to move to the player's position.  */
	MoveToPlayer = 1,
	/**  State to flee or move away from the player.  */
	Flee = 2
};

/**
 * AI controller class that implements a controller for an NPC with state machine.
 * This class handles the behavior and decisions of the NPC using a state machine.
 */
UCLASS()
class AIOVERVIEWTHESIS_API AStateMachineAIController : public AAIController
{
	GENERATED_BODY()

private:

	// Current state machine that the AI is currently in.
	EAIStateMachines CurrentStateMachine;

	// Radius used for determining random points in the world.
	UPROPERTY(EditDefaultsOnly, Category = Thesis)
	float RandomPointRadius = 500.0f;
	
protected:

	/**
	* @brief Called when this AI controller "possesses" a pawn (usually a playable character).
	*/
	virtual void OnPossess(APawn* InPawn) override;

	/**
	* @brief Called at the beginning of the game for this AI controller.
	*/
	virtual void BeginPlay() override;

	/**
	* @brief Tries to move the AI towards a specific location.
	* 
	* @param AIDestination The location the AI will attempt to move to.
	*/
	void TryingToMoveAI(const FVector& AIDestination);


	/**
	* @brief Called when a requested movement by the AI is completed.
	* 
	* @param RequestID The ID of the movement request.
	* @param Result The result of the movement.
	*/
	virtual void OnMoveCompleted(FAIRequestID RequestID, const FPathFollowingResult& Result) override;

	/**
	* @brief Gets a random point and then tries to move the AI towards that point.
	*/
	void GetRandomPointAndTryingToMoveAI();
	
public:

	/**
	* @brief Gets a random point in the world.
	* 
	* @param DestinationToMove The random location obtained.
	*/
	void GetRandomPoint(FVector& DestinationToMove) const;
};
