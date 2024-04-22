// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "AIStateTreeCharacter.generated.h"

/**
 * A custom character class that integrates with the State Tree system.
 * This class extends ACharacter to include functionality related to State Trees.
 */
UCLASS()
class AIOVERVIEWTHESIS_API AAIStateTreeCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AAIStateTreeCharacter();

	/**
	* Returns the State Tree component attached to this character.
	* @return The State Tree component.
	*/
	UFUNCTION(BlueprintPure, Category = "Thesis")
	UStateTreeComponent* GetStateTreeComponent() const { return StateTreeComponent; }

protected:

	/**
	* The State Tree component attached to this character.
	* This component manages the character's state transitions and behaviors.
	*/
	UPROPERTY(VisibleDefaultsOnly, Category = "Thesis")
	UStateTreeComponent* StateTreeComponent;
};
