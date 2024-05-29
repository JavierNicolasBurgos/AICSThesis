// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "UtilityAction.generated.h"


class UUtilityConsideration;

/**
 * Abstract base class for defining utility actions in the Utility AI system.
 */
UCLASS(Abstract, BlueprintType, Blueprintable)
class AIOVERVIEWTHESIS_API UUtilityAction : public UObject
{
	GENERATED_BODY()

public:

	/**
	* @brief Set of consideration types that influence this action.
	*/
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Thesis|UtilityAI")
	TSet<TSubclassOf<UUtilityConsideration>> ConsiderationTypes;

	/**
	* @brief Array of instantiated considerations for this action.
	*/
	UPROPERTY(BlueprintReadOnly, Category = "Thesis|UtilityAI")
	TArray<UUtilityConsideration*> Considerations;

protected:

	/**
	* @brief Reference to the owning Utility AI component.
	*/
	UPROPERTY()
	UUtilityAIComponent* UtilityAIComponent;

	/**
	* @brief Reference to the AI controller executing this action.
	*/
	UPROPERTY()
	AAIController* AIController;

	/**
	* @brief The calculated score of this action based on its considerations.
	*/
	UPROPERTY()
	float Score;

	/**
	* @brief Flag indicating if the action is currently being executed.
	*/
	bool bExecutingAction;

public:

	/**
	* @brief Default constructor.
	*/
	UUtilityAction();

	/**
	* @brief Gets the world context for this action.
	* @return The world context.
	*/
	virtual UWorld* GetWorld() const override;
	
	/**
	* @brief Initializes the variables for this action.
	* @param InUtilityAIComponent The owning Utility AI component.
	* @param InAIController The AI controller executing this action.
	*/
	void InitializeVariables(UUtilityAIComponent* InUtilityAIComponent, AAIController* InAIController);

	/**
	* @brief Creates and initializes the considerations for this action.
	*/
	virtual void CreateConsiderations();

	/**
	* @brief Sets the score for this action.
	* @param Value The new score value.
	*/
	UFUNCTION(BlueprintCallable, Category = "Thesis|UtilityAI")
	void SetScore(float Value);

	/**
	* @brief Checks if the action is currently being executed.
	* @return True if the action is being executed, false otherwise.
	*/
	UFUNCTION(BlueprintPure, Category = "Thesis|UtilityAI")
	bool IsExecutingAction() const;

	/**
	* @brief Gets the score of this action.
	* @return The score of this action.
	*/
	UFUNCTION(BlueprintPure, Category = "Thesis|UtilityAI")
	float GetScore() const;

	/**
	* @brief Blueprint native event for constructing the action.
	*/
	UFUNCTION(BlueprintNativeEvent, Category = "Thesis|UtilityAI")
	void Construct();

	/**
	* @brief Executes the action.
	*/
	void ExecuteAction();

	/**
	* @brief Finishes the action.
	*/
	UFUNCTION(BlueprintCallable, Category = "Thesis|UtilityAI")
	void FinishAction();

	/**
	* @brief Cancels the action.
	*/
	UFUNCTION(BlueprintCallable, Category = "Thesis|UtilityAI")
	void CancelAction();

	/**
	* @brief Blueprint native event to determine if the action can be canceled.
	* @return True if the action can be canceled, false otherwise.
	*/
	UFUNCTION(BlueprintNativeEvent, Category = "Thesis|UtilityAI")
	bool CanCancelAction();

protected:

	/**
	* @brief Gets the owning Utility AI component.
	* @return The Utility AI component.
	*/
	UFUNCTION(BlueprintPure, Category = "Thesis|UtilityAI")
	UUtilityAIComponent* GetUtilityAIComponent() const;

	/**
	* @brief Gets the AI controller executing this action.
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
	* @brief Blueprint native event to start the action.
	*/
	UFUNCTION(BlueprintNativeEvent, Category = "Thesis|UtilityAI")
	void StartAction();

	/**
	* @brief Blueprint native event to stop the action.
	* @param bCanceled Indicates if the action was canceled.
	*/
	UFUNCTION(BlueprintNativeEvent, Category = "Thesis|UtilityAI")
	void StopAction(bool bCanceled);
	
};
