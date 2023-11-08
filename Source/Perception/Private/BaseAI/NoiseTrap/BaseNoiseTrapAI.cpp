// Fill out your copyright notice in the Description page of Project Settings.


#include "BaseAI/NoiseTrap/BaseNoiseTrapAI.h"

// Sets default values
ABaseNoiseTrapAI::ABaseNoiseTrapAI()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void ABaseNoiseTrapAI::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ABaseNoiseTrapAI::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void ABaseNoiseTrapAI::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

