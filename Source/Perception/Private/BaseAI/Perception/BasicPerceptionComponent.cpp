// Fill out your copyright notice in the Description page of Project Settings.


#include "BaseAI/Perception/BasicPerceptionComponent.h"

UBasicPerceptionComponent::UBasicPerceptionComponent()
{

	/*SightConfig = CreateDefaultSubobject<UAISenseConfig_Sight>(TEXT("Sight Perception"));
	UBasicPerceptionComponent::ConfigureSense(*SightConfig);
	
	HearingConfig = CreateDefaultSubobject<UAISenseConfig_Hearing>(TEXT("Hearing Perception"));
	UBasicPerceptionComponent::ConfigureSense(*HearingConfig);*/
}

/*
void UBasicPerceptionComponent::SetupPerceptionSystem()
{

if (SightConfig)
{
	SightConfig->SightRadius = 400.f;
	SightConfig->LoseSightRadius = SightConfig->SightRadius + 25.f;
	SightConfig->PeripheralVisionAngleDegrees = 90.f;
	SightConfig->SetMaxAge(5.f);

	// Allows Ai to continue to see stimulis source if it remains within specified distance from last seen location 
	SightConfig->AutoSuccessRangeFromLastSeenLocation = 520.f;
	SightConfig->DetectionByAffiliation.bDetectEnemies = true;
	SightConfig->DetectionByAffiliation.bDetectFriendlies = true;
	SightConfig->DetectionByAffiliation.bDetectNeutrals = true;

	// Sets the dominant sense ( The main sense)
	SetDominantSense(*SightConfig->GetSenseImplementation());
	//OnTargetPerceptionForgotten.AddDynamic(this, &UBasicPerceptionComponent::OnTargetDetected);
	ConfigureSense(*SightConfig);
}
}

void UBasicPerceptionComponent::OnTargetDetected(AActor* Actor, FAIStimulus const Stimulus)
{
}
*/
