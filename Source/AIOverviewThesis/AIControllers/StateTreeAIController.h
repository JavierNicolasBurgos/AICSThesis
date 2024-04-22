// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AIControllerBase.h"
#include "StateTreeAIController.generated.h"

class UStateTreeComponent;

/**
*  AI controller class that implements a controller for an NPC with State Trees.
 * This class handles the behavior and decisions of the NPC using a State Trees.
 */
UCLASS()
class AIOVERVIEWTHESIS_API AStateTreeAIController : public AAIControllerBase
{
	GENERATED_BODY()

protected:

	/**
	* @brief Callback function that is invoked when the AI perception system is updated.
	* @param Actor The actor that triggered the perception update.
	* @param Stimulus The stimulus information received from the actor.
	*/
	virtual void PerceptionUpdated(AActor* Actor, FAIStimulus Stimulus) override;
};
