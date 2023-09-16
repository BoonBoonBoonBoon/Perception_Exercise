// Fill out your copyright notice in the Description page of Project Settings.


#include "BaseAI/ChaseAI/ChaseAI.h"

// Sets default values
AChaseAI::AChaseAI()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AChaseAI::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AChaseAI::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void AChaseAI::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

