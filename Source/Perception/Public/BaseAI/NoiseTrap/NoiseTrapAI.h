// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameplayTagContainer.h"
#include "GenericTeamAgentInterface.h"
#include "GameFramework/Character.h"
#include "Perception/AIPerceptionStimuliSourceComponent.h"
#include "Perception/AISightTargetInterface.h"
#include "NoiseTrapAI.generated.h"

UCLASS()
class PERCEPTION_API ANoiseTrapAI : public ACharacter, public IAISightTargetInterface, public IGenericTeamAgentInterface
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	ANoiseTrapAI();

	// Team Number, this will be used to determine the groups
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AI")
	int32 ID = 2;

	// Get Team Id
	virtual FGenericTeamId GetGenericTeamId() const override {return TeamId;};

protected:

	// Team ID
	FGenericTeamId TeamId = 2;


	
public:
	
	/*UPROPERTY(EditAnywhere)
	FGameplayTag NoiseTrapTag; */
	
	// Used as a generator for the pawn to emit a stimuli. Need this as the AI will use this as a tool to percept.
	UPROPERTY()
	UAIPerceptionStimuliSourceComponent* StimuliSourcePredator;
	
	void SetupStimulusSource();

	// The function that plays the sound (USound is the class that's responsible for playable sound object)
	UFUNCTION(BlueprintCallable, Category=AI)
	void ReportNoise(USoundBase* SoundToPlay, float Volume);

	// Emitter component used to emit the sound to nearby ai.
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UPawnNoiseEmitterComponent* NoiseEmitter;
	
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

};
