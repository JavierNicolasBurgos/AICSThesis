// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "NativeGameplayTags.h"
#include "AIHelpersLibrary.generated.h"

UE_DECLARE_GAMEPLAY_TAG_EXTERN(TAG_AI_STATES_NONE);
UE_DECLARE_GAMEPLAY_TAG_EXTERN(TAG_AI_STATES_PATROL);
UE_DECLARE_GAMEPLAY_TAG_EXTERN(TAG_AI_STATES_MOVETO_PLAYER);
UE_DECLARE_GAMEPLAY_TAG_EXTERN(TAG_AI_STATES_MOVETO_LASTSTIMULUSLOCATION);

/**
 * Help library containing AI-related functions, gameplay tags, accessible in Blueprints or C++.
 */
UCLASS()
class AIOVERVIEWTHESIS_API UAIHelpersLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:
	
	/**
	* Retrieves the name of the Blackboard key used for storing the target location in AI logic.
	* @return The name of the blackboard key for the last stimulus location.
	*/
	UFUNCTION(BlueprintPure, Category="Thesis")
	static FName GetTargetLocationName();

	/**
	* Returns the name of the blackboard key used to store the last stimulus location.
	* @return The name of the blackboard key for the last stimulus location.
	*/
	UFUNCTION(BlueprintPure, Category="Thesis")
	static FName GetLastStimulusLocationName();

	/**
	* Returns the name of the blackboard key used to store the target actor.
	* @return The name of the blackboard key for the target actor.
	*/
	UFUNCTION(BlueprintPure, Category="Thesis")
	static FName GetTargetActorName();
};
