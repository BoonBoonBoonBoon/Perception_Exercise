// Fill out your copyright notice in the Description page of Project Settings.


#include "BaseAI/AIBase_PawnSensingComponent.h"
#include "Perception\Public\BaseAI\AIBase.h"


UAIBase_PawnSensingComponent::UAIBase_PawnSensingComponent()
{

	// Currently not intrested in player pawns 
	bOnlySensePlayers = false;

	// Sensing food pawns
	bSeePawns = true;


	// IsSenseActor()
}

void UAIBase_PawnSensingComponent::BeginPlay()
{
	Super::BeginPlay();
}
