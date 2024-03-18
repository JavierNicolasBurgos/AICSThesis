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
	* @brief Checks if the angle is within the AI's field of view range.
	* For example a field of view angle of 90 degrees.
	*/
	UPROPERTY(EditDefaultsOnly, Category = "Thesis|AI|Vision", meta = (ClampMin = "0", ClampMax = "180", UIMin = "0", UIMax = "180"))
	float AIFieldOfView = 90.0f;

	/**
	 * @brief The distance at which the AI loses sight of the player.
	 * It represents the radius within which the AI stops tracking the player's position.
	 */
	UPROPERTY(EditDefaultsOnly, Category = "Thesis|AI|Vision", meta = (UIMin = 0.0, ClampMin = 0.0))
	float LoseSightRadius = 1000.0f;

	/**
	 * Timer handle for controlling the wait time before initiating movement.
	 */
	FTimerHandle WaitTimerHandle;
	
protected:

	/**
	* @brief Called when this AI controller "possesses" a pawn (usually a playable character).
	*/
	virtual void OnPossess(APawn* InPawn) override;
	
	/**
	 * @brief Overrides the Tick function to perform AI logic on each frame update.
	 * @param DeltaSeconds The time elapsed since the last frame.
	 */
	virtual void Tick(float DeltaSeconds) override;

	/**
	* @brief Checks if the AI can see the player.
	* @return True if the AI can see the player, false otherwise.
	*/
	bool CanSeePlayer() const;

	/**
	* @brief Calculates the view angle between the AI and the player.
	* @param PlayerCharacter The player character to calculate the view angle to.
	* @return The view angle in degrees between the AI and the player.
	*/
	float  CalculateViewAngleToPlayer(const ACharacter* PlayerCharacter) const;

	/**
	 * @brief Calculates the squared distance between the AI and the player character.
	 * @param PlayerCharacter The player character whose distance to the AI is being calculated.
	 * @return The squared distance between the AI and the player character.
	 */
	float CalculateSquaredDistanceToPlayer(const ACharacter* PlayerCharacter) const;

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
	* @brief This function resumes the random movement of the AI after a wait time.
	* Calculates a new random waiting time within the range specified by the base waiting time and the deviation.
	* Once the waiting time has elapsed, the function is called to obtain a new random point and move the character to it.
	*/
	void ResumeRandomMovementAfterWaitTime();

};
