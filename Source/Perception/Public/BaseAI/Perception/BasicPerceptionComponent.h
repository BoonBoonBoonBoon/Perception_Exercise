// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Perception/AIPerceptionComponent.h"
#include "Perception/AISenseConfig_Hearing.h"
#include "Perception/AISenseConfig_Sight.h"
#include "BasicPerceptionComponent.generated.h"

/**
 * 
 */
UCLASS()
class PERCEPTION_API UBasicPerceptionComponent : public UAIPerceptionComponent
{
	GENERATED_BODY()
public:

	UBasicPerceptionComponent();

	/*// Configuration for senses under perception class 
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Sight Perception")
	UAISenseConfig_Sight* SightConfig;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Hearing Perception")
	UAISenseConfig_Hearing* HearingConfig;

	void SetupPerceptionSystem();

	UFUNCTION()
	void OnTargetDetected(AActor* Actor, FAIStimulus const Stimulus);*/
	
	// Array which holds the Sensconfig elements 
/*
UPROPERTY(EditDefaultsOnly, Instanced, Category="AI Perception")
	TArray<UAISenseConfig*> SensesConfigArray;
	*/
	
protected:

private:

	
};
