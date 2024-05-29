// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "UtilityConsideration.generated.h"

/**
 * Abstract base class for defining utility considerations in the Utility AI system.
 */
UCLASS(Abstract, BlueprintType, Blueprintable)
class AIOVERVIEWTHESIS_API UUtilityConsideration : public UObject
{
	GENERATED_BODY()

public:

	/**
	* @brief Curve used to evaluate the response of the consideration.
	*/
	UPROPERTY(SaveGame,EditAnywhere, Category = "Thesis|UtilityAI")
	FRuntimeFloatCurve ResponseCurve;

protected:

	/**
	* @brief Reference to the owning Utility AI component.
	*/
	UPROPERTY()
	UUtilityAIComponent* UtilityAIComponent;

	/**
	* @brief Reference to the AI controller evaluating this consideration.
	*/
	UPROPERTY()
	AAIController* AIController;

	/**
	* @brief The calculated score of this consideration.
	*/
	UPROPERTY()
	float Score;

public:

	/**
	* @brief Default constructor.
	*/
	UUtilityConsideration();

	/**
	* @brief Gets the world context for this consideration.
	* @return The world context.
	*/
	virtual UWorld* GetWorld() const override;

	/**
	* @brief Initializes the variables for this consideration.
	* @param InUtilityAIComponent The owning Utility AI component.
	* @param InAIController The AI controller evaluating this consideration.
	*/
	void InitializeVariables(UUtilityAIComponent* InUtilityAIComponent, AAIController* InAIController);

	/**
	* @brief Gets the score of this consideration.
	* @return The score of this consideration.
	*/
	UFUNCTION(BlueprintPure, Category = "Thesis|UtilityAI")
	float GetScore() const;

	/**
	* @brief Blueprint native event for constructing the consideration.
	*/
	UFUNCTION(BlueprintNativeEvent)
	void Construct();

	/**
	* @brief Evaluates and returns the score of this consideration.
	* @return The evaluated score.
	*/
	float EvaluateScore();

protected:

	/**
	* @brief Gets the owning Utility AI component.
	* @return The Utility AI component.
	*/
	UFUNCTION(BlueprintPure, Category = "Thesis|UtilityAI")
	UUtilityAIComponent* GetUtilityAIComponent() const;

	/**
	* @brief Gets the AI controller evaluating this consideration.
	* @return The AI controller.
	*/
	UFUNCTION(BlueprintPure, Category = "Thesis|UtilityAI")
	AAIController* GetAIController() const;

	/**
	* @brief Gets the pawn controlled by the AI controller.
	* @return The pawn.
	*/
	UFUNCTION(BlueprintPure, Category = "Thesis|UtilityAI")
	APawn* GetPawn() const;

	/**
	* @brief Blueprint native event for scoring the consideration.
	* @return The scored value of the consideration.
	*/
	UFUNCTION(BlueprintNativeEvent, Category = "Thesis|UtilityAI")
	float ScoreConsideration();
};
