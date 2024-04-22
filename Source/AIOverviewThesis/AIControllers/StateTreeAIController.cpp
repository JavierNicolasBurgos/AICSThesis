// Fill out your copyright notice in the Description page of Project Settings.


#include "StateTreeAIController.h"

#include "AIOverviewThesis/AIHelpers/AIHelpersLibrary.h"
#include "AIOverviewThesis/Characters/AIStateTreeCharacter.h"
#include "Components/StateTreeComponent.h"


void AStateTreeAIController::PerceptionUpdated(AActor* Actor, FAIStimulus Stimulus)
{
	Super::PerceptionUpdated(Actor, Stimulus);

	const AAIStateTreeCharacter* StateTreeCharacter = CastChecked<AAIStateTreeCharacter>(GetCharacter());
	UStateTreeComponent* StateTreeComponent = StateTreeCharacter->GetStateTreeComponent();
	
	if (Stimulus.WasSuccessfullySensed())
	{
		StateTreeComponent->SendStateTreeEvent(TAG_AI_STATES_MOVETO_PLAYER);
	}
	else
	{
		StateTreeComponent->SendStateTreeEvent(TAG_AI_STATES_MOVETO_LASTSTIMULUSLOCATION);
	}
}
