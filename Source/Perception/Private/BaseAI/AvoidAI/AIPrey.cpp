// Fill out your copyright notice in the Description page of Project Settings.


#include "BaseAI/AvoidAI/AIPrey.h"

#include "Perception/AIPerceptionStimuliSourceComponent.h"
#include "Perception/AISenseConfig_Sight.h"

// Sets default values
AAIPrey::AAIPrey()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

void AAIPrey::SetupStim()
{
	// Setup Stim Component.
	StimSource = CreateDefaultSubobject<UAIPerceptionStimuliSourceComponent>(TEXT("StimSource"));
	if(StimSource)
	{
		// Registers owning actor as source for specified class.
		// TSub lets you restrict the types that can be assigned.
		StimSource->RegisterForSense(TSubclassOf<UAISense_Sight>());
		
	}
	
}

// Called when the game starts or when spawned
void AAIPrey::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AAIPrey::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void AAIPrey::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

