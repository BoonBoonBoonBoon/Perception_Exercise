// Fill out your copyright notice in the Description page of Project Settings.


#include "BaseAI/PreyAI/PreyAIPawn.h"

#include "GameFramework/CharacterMovementComponent.h"

// Sets default values
APreyAIPawn::APreyAIPawn()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	GetCharacterMovement()->MaxWalkSpeed = 300;
}

// Called when the game starts or when spawned
void APreyAIPawn::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void APreyAIPawn::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void APreyAIPawn::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

