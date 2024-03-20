// Fill out your copyright notice in the Description page of Project Settings.


#include "BehaviorTreeAIController.h"

void ABehaviorTreeAIController::OnPossess(APawn* InPawn)
{
	Super::OnPossess(InPawn);
	RunBehaviorTree(BTToRun);
}
