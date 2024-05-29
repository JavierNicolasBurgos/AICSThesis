// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "UtilityAIComponent.generated.h"

class AAIController;

/*
* Enum for defining how the Utility AI updates its best action selection.
*/
UENUM(BlueprintType)
enum class EUtilityUpdate : uint8
{
	None,
	Tick,
	Timer,
};

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnSelectAction, UUtilityAction*, Value);

/**
 * Component to handle Utility system.
 */
UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class AIOVERVIEWTHESIS_API UUtilityAIComponent : public UActorComponent
{
	GENERATED_BODY()

public:
	
	/** 
	* @brief Event triggered when a new action is selected by the Utility AI.
	*/
	UPROPERTY(BlueprintAssignable, Category = "Thesis|UtilityAI")
	FOnSelectAction OnSelectAction;

protected:

	/** 
	* @brief Set of actions available to the Utility AI.
	*/
	UPROPERTY()
	TSet<UUtilityAction*> Actions;

	/** 
	* @brief The current action being executed by the Utility AI.
	*/
	UPROPERTY()
	UUtilityAction* CurrentAction = nullptr;
	
	/** 
	* @brief Set of default action types that the Utility AI can choose from.
	*/
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Thesis|UtilityAI")
	TSet<TSubclassOf<UUtilityAction>> DefaultActionTypes;

	/** 
	* @brief The method used to update the selection of the best action.
	*/
	UPROPERTY(EditAnywhere, Category = "Thesis|UtilityAI")
	EUtilityUpdate SelectBestActionUpdateType = EUtilityUpdate::Timer;

	/** 
	* @brief Timer rate for selecting the best action when using the Timer update type.
	* @param SelectBestActionUpdateType The type of update used for selecting the best action.
	*/
	UPROPERTY(EditAnywhere, Category = "Thesis|UtilityAI", meta = (EditCondition = "SelectBestActionUpdateType==EUtilityUpdate::Timer", EditConditionHides))
	float SelectBestActionTimerRate = 1;

	/** 
	* @brief Flag to decide if a random action should be selected if selecting the best action fails.
	*/
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Thesis|UtilityAI")
	bool bRandomActionIfSelectBestActionFails = true;

	/** 
	* @brief Reference to the AI Controller owning this component.
	*/
	UPROPERTY()
	AAIController* AIController = nullptr;

	/** 
	* @brief Flag indicating if an action selection process is ongoing.
	*/
	bool bSelectingAction;

	/** 
	* @brief Timer handle for managing the action selection timer.
	*/
	UPROPERTY()
	FTimerHandle TimerHandle;

private:

public:

	/**
	* @brief Sets default values for this component's properties.
	*/
	UUtilityAIComponent();

	/** 
	* @brief Called when the component is registered.
	*/
	virtual void OnRegister() override;

	/** 
	* @brief Called when the game starts.
	*/
	virtual void BeginPlay() override;

	/** 
	* @brief Called every frame to update the component.
	* @param DeltaTime Time elapsed since the last frame.
	* @param TickType Type of tick this is, for example, are we paused, or 'simulating' in the editor.
	* @param ThisTickFunction Internal tick function struct that caused this to run.
	*/
	virtual void TickComponent(float DeltaTime, enum ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	/** 
	* @brief Returns the list of actions available to the Utility AI.
	* @return An array of available actions.
	*/
	UFUNCTION(BlueprintPure, Category = "Thesis|UtilityAI")
	TArray<UUtilityAction*> GetActions() const;

	/** 
	* @brief Returns the current action being executed by the Utility AI.
	* @return The current action.
	*/
	UFUNCTION(BlueprintPure, Category = "Thesis|UtilityAI")
	UUtilityAction* GetCurrentAction() const;

	/** 
	* @brief Sets the update type for selecting the best action and optionally updates the timer rate.
	* @param Value The new update type.
	* @param TimerRate The new timer rate, default is 0.5f.
	*/
	UFUNCTION(BlueprintCallable, Category = "Thesis|UtilityAI")
	void SetSelectBestActionUpdateType(EUtilityUpdate Value, float TimerRate = .5f);


	/** 
	* @brief Returns the current update type used for selecting the best action.
	* @return The current update type.
	*/
	UFUNCTION(BlueprintPure, Category = "Thesis|UtilityAI")
	EUtilityUpdate GetSelectBestActionUpdateType() const;

	/** 
	* @brief Returns the instance of an action based on its class.
	* @param ActionClass The class of the action to retrieve.
	* @return The action instance, or nullptr if not found.
	*/
	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "Thesis|UtilityAI")
	UUtilityAction* GetActionInstanceByClass(TSubclassOf<UUtilityAction> ActionClass) const;

	/** 
	* @brief Returns whether the Utility AI is currently in the process of selecting an action.
	* @return True if selecting an action, false otherwise.
	*/
	UFUNCTION(BlueprintCallable, Category = "Thesis|UtilityAI")
	bool IsSelectingAction() const;

	/** 
	* @brief Selects the best action for the Utility AI based on defined criteria.
	*/
	UFUNCTION(BlueprintCallable, Category = "Thesis|UtilityAI")
	virtual void SelectBestAction();

	
	/** 
	* @brief Adds a new action to the Utility AI's set of actions.
	* @param ActionType The class type of the action to add.
	* @return True if the action was added successfully, false otherwise.
	*/
	UFUNCTION(BlueprintCallable, Category = "Thesis|UtilityAI")
	bool AddAction(TSubclassOf<UUtilityAction> ActionType);

	/** 
	* @brief Removes an action from the Utility AI's set of actions.
	* @param ActionType The class type of the action to remove.
	* @return True if the action was removed successfully, false otherwise.
	*/
	UFUNCTION(BlueprintCallable, Category = "Thesis|UtilityAI")
	bool RemoveAction(TSubclassOf<UUtilityAction> ActionType);

protected:
	
	/** 
	* @brief Creates the default set of actions for the Utility AI.
	*/
	virtual void CreateDefaultActions();

	/** 
	* @brief Scores a given action to determine its utility.
	* @param Action The action to score.
	* @return The score of the action.
	*/
	virtual float ScoreAction(UUtilityAction* Action);	
};
