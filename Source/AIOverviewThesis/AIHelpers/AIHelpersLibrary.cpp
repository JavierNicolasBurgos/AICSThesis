// Fill out your copyright notice in the Description page of Project Settings.


#include "AIHelpersLibrary.h"

UE_DEFINE_GAMEPLAY_TAG(TAG_AI_STATES_NONE, "AI.States.None");
UE_DEFINE_GAMEPLAY_TAG(TAG_AI_STATES_PATROL, "AI.States.Patrol");
UE_DEFINE_GAMEPLAY_TAG(TAG_AI_STATES_MOVETO_PLAYER, "AI.States.MoveTo.Player");
UE_DEFINE_GAMEPLAY_TAG(TAG_AI_STATES_MOVETO_LASTSTIMULUSLOCATION, "AI.States.MoveTo.LastStimulusLocation");

FName UAIHelpersLibrary::GetTargetLocationName()
{
	return FName("TargetLocation");
}

FName UAIHelpersLibrary::GetLastStimulusLocationName()
{
	return FName("LastStimulusLocation");
}

FName UAIHelpersLibrary::GetTargetActorName()
{
	return FName("TargetActor");
}
