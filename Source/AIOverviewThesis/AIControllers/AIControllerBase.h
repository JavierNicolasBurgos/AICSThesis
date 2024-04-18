// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "Perception/AIPerceptionTypes.h"
#include "AIControllerBase.generated.h"

class UAISenseConfig_Sight;

/**
 * Base AI Controller class providing foundational AI functionality.
 */
UCLASS()
class AIOVERVIEWTHESIS_API AAIControllerBase : public AAIController
{
	GENERATED_BODY()

protected:

	/**
	* @brief Configuration of the visual perception (sense of sight) of the AI.
	* This setting defines the visual detection parameters for the AI.
	*/
	UAISenseConfig_Sight* AISenseConfigSight = nullptr;

	/**
	* @brief Called at the beginning of the game for this AI controller.
	*/
	virtual void BeginPlay() override;

	/**
	* @brief Callback function that is invoked when the AI perception system is updated.
	* @param Actor The actor that triggered the perception update.
	* @param Stimulus The stimulus information received from the actor.
	*/
	UFUNCTION()
	virtual void PerceptionUpdated(AActor* Actor, FAIStimulus Stimulus);
	
public:

	/**
	* @brief Constructor of the AStateMachineAIController class.
	* Initializes the properties and settings needed for the AI.
	*/
	AAIControllerBase();
	
};
