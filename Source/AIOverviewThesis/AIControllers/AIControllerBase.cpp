// Fill out your copyright notice in the Description page of Project Settings.


#include "AIControllerBase.h"
#include "Perception/AIPerceptionComponent.h"
#include "Perception/AISenseConfig_Sight.h"

void AAIControllerBase::BeginPlay()
{
	Super::BeginPlay();

	PerceptionComponent->OnTargetPerceptionUpdated.AddUniqueDynamic(this, &AAIControllerBase::PerceptionUpdated);
}

void AAIControllerBase::PerceptionUpdated(AActor* Actor, FAIStimulus Stimulus)
{
	
}

AAIControllerBase::AAIControllerBase()
{
	PerceptionComponent = CreateDefaultSubobject<UAIPerceptionComponent>("PerceptionComponent");
	AISenseConfigSight = CreateDefaultSubobject<UAISenseConfig_Sight>("SenseSight");
	AISenseConfigSight->DetectionByAffiliation.bDetectEnemies = true;
	AISenseConfigSight->DetectionByAffiliation.bDetectFriendlies = true;
	AISenseConfigSight->DetectionByAffiliation.bDetectNeutrals = true;

	PerceptionComponent->ConfigureSense(*AISenseConfigSight);
	PerceptionComponent->SetDominantSense(UAISenseConfig_Sight::StaticClass());
}
