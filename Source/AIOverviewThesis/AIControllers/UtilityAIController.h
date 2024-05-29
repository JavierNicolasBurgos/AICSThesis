// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AIControllerBase.h"
#include "UtilityAIController.generated.h"

class UUtilityAIComponent;

/**
* AI controller class that implements a controller for an NPC with Utility AI technique.
* This class handles the behavior and decisions of the NPC using an Utility AI technique.
*/
UCLASS()
class AIOVERVIEWTHESIS_API AUtilityAIController : public AAIControllerBase
{
	GENERATED_BODY()

public:

	/**
	* Constructor for initializing default values and setting up the Utility AI Component.
	*/
	AUtilityAIController();

	/*
	* Function to retrieve the Utility AI Component.
	* This function is BlueprintPure, meaning it does not modify the object and can be used in Blueprint read-only contexts.
	*/
	UFUNCTION(BlueprintPure, Category = "Thesis|UtilityAI")
	UUtilityAIComponent* GetUtilityAIComponent() const { return UtilityAIComponent; }

protected:

	/*
	* Property to hold the Utility AI Component.
	* VisibleAnywhere allows it to be seen in the editor, but not modified.
	*/
	UPROPERTY(VisibleAnywhere, Category = "Thesis|UtilityAI")
	UUtilityAIComponent* UtilityAIComponent = nullptr;
};
