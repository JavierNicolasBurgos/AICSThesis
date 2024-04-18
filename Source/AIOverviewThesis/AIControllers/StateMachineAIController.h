// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AIControllerBase.h"
#include "Perception/AIPerceptionTypes.h"
#include "StateMachineAIController.generated.h"

class UAISenseConfig_Sight;

UENUM()
enum EAIStateMachines
{
	/** Default state, representing no specific action. */
	None = 0,
	/** State to patrol a given area or route. */
	Patrol = 1,
	/** State to move to the player's position.  */
	MoveToPlayer = 2,
	/** State to move to the last known stimulus location. */
	MoveToLastStimulusLocation = 3
};

/**
 * AI controller class that implements a controller for an NPC with state machine.
 * This class handles the behavior and decisions of the NPC using a state machine.
 */
UCLASS()
class AIOVERVIEWTHESIS_API AStateMachineAIController : public AAIControllerBase
{
	GENERATED_BODY()

private:

	/*
	* Current state machine that the AI is currently in.
	*/
	EAIStateMachines CurrentStateMachine;

	/**
	* @brief Stores the last location of the sensory stimulus perceived by the AI.
	* Value initialized to an invalid location.
	*/
	FVector LastStimulusLocation = FAISystem::InvalidLocation;

	/**
	 * Radius used for determining random points in the world.
	 */
	UPROPERTY(EditDefaultsOnly, Category = "Thesis|AI|Movement")
	float RandomPointRadius = 500.0f;

	/**
	 * Waiting time after arriving at a point previously moved to.
	 * After this time, the AI will move to another random point.
	 */
	UPROPERTY(EditDefaultsOnly, Category = "Thesis|AI|Movement")
	float WaitTime = 3.0f;

	/**
	* Variable deviation that can be added to or subtracted from the WaitTime after reaching the point.
	* This deviation is a random value.
	*/
	UPROPERTY(EditDefaultsOnly, Category = "Thesis|AI|Movement")
	float WaitTimeRandomDeviation = 0.0f;

	/**
	 * The acceptable range from a destination point within which the AI considers it has reached its goal.
	 */
	UPROPERTY(EditDefaultsOnly, Category = "Thesis|AI|Movement", meta = (UIMin = 0.0, ClampMin = 0.0))
	float AcceptanceRadius = 100.0f;

	/**
	* @brief Indicates whether the AI can currently see the player.
	*/
	bool bCanSeePlayer = false;

	/**
	 * Timer handle for controlling the wait time before initiating movement.
	 */
	FTimerHandle WaitTimerHandle;

protected:

	/**
	 * @brief Overrides the Tick function to perform AI logic on each frame update.
	 * @param DeltaSeconds The time elapsed since the last frame.
	 */
	virtual void Tick(float DeltaSeconds) override;

	/**
	* @brief Called at the beginning of the game for this AI controller.
	*/
	virtual void BeginPlay() override;

	/**
	* @brief Clears the wait timer if it is valid, preventing further execution of the wait period.
	*/
	void ClearWaitTimer();

	/**
	* @brief Gets a random point and then tries to move the AI towards that point.
	*/
	void GetRandomPointAndTryingToMoveAI();

	/**
	* @brief Gets a random point in the world.
	* 
	* @param DestinationToMove The random location obtained.
	*/
	void GetRandomPoint(FVector& DestinationToMove) const;
	
	/**
	* @brief Called when a requested movement by the AI is completed.
	* 
	* @param RequestID The ID of the movement request.
	* @param Result The result of the movement.
	*/
	virtual void OnMoveCompleted(FAIRequestID RequestID, const FPathFollowingResult& Result) override;
	
	/**
	* @brief This function resumes the random movement of the AI after a wait time.
	* Calculates a new random waiting time within the range specified by the base waiting time and the deviation.
	* Once the waiting time has elapsed, the function is called to obtain a new random point and move the character to it.
	*/
	void ResumeRandomMovementAfterWaitTime();

	/**
	* @brief Callback function that is invoked when the AI perception system is updated.
	* @param Actor The actor that triggered the perception update.
	* @param Stimulus The stimulus information received from the actor.
	*/
	virtual void PerceptionUpdated(AActor* Actor, FAIStimulus Stimulus) override;

public:

	/**
	* @brief Sets the current state of the AI state machine.
	* @param InState The new state to set.
	*/
	void SetCurrentState(EAIStateMachines InState);
};
