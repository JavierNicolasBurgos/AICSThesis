// Fill out your copyright notice in the Description page of Project Settings.


#include "AIStateTreeCharacter.h"
#include "Components/StateTreeComponent.h"


AAIStateTreeCharacter::AAIStateTreeCharacter()
{
	PrimaryActorTick.bCanEverTick = false;

	StateTreeComponent = CreateDefaultSubobject<UStateTreeComponent>(TEXT("StateTreeComponent"));
}