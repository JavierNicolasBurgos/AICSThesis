// Fill out your copyright notice in the Description page of Project Settings.


#include "UtilityAIController.h"
#include "AIOverviewThesis/Components/AIComponents/UtilityAIComponent.h"

AUtilityAIController::AUtilityAIController()
{
	UtilityAIComponent = CreateDefaultSubobject<UUtilityAIComponent>(TEXT("UtilityAIComponent"));
}
