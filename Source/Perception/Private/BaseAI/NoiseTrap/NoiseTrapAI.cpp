// Fill out your copyright notice in the Description page of Project Settings.


#include "BaseAI/NoiseTrap/NoiseTrapAI.h"

#include "Components/PawnNoiseEmitterComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Perception/AISense_Hearing.h"
#include "Perception/AISense_Sight.h"

// Sets default values
ANoiseTrapAI::ANoiseTrapAI()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	NoiseEmitter = CreateDefaultSubobject<UPawnNoiseEmitterComponent>(TEXT("PawnNoiseEmitter");
}

void ANoiseTrapAI::SetupStimulusSource()
{
	StimuliSourcePredator = CreateDefaultSubobject<UAIPerceptionStimuliSourceComponent>(TEXT("Stimulus Source"));
	if(StimuliSourcePredator)
	{
		StimuliSourcePredator->RegisterForSense(TSubclassOf<UAISense_Sight>());
		StimuliSourcePredator->RegisterForSense(TSubclassOf<UAISense_Hearing>());
		StimuliSourcePredator->RegisterWithPerceptionSystem();
	}
}

void ANoiseTrapAI::ReportNoise(USoundBase* SoundToPlay, float Volume)
{
	if(SoundToPlay)
	{
		// Plays the actual sound
		UGameplayStatics::PlaySoundAtLocation(GetWorld(),SoundToPlay, GetActorLocation(), Volume);

		//Report we played a sound at a certain volume in a specific location
		MakeNoise(Volume, this, GetActorLocation());
	}
}

// Called when the game starts or when spawned
void ANoiseTrapAI::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ANoiseTrapAI::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void ANoiseTrapAI::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

