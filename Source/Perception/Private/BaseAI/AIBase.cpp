// Fill out your copyright notice in the Description page of Project Settings.


#include "BaseAI/AIBase.h"

// Sets default values
AAIBase::AAIBase()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;


	// Pawn sensing
	PawnSensingComponent = CreateDefaultSubobject<UAIBase_PawnSensingComponent>(TEXT("Perception"));

	
	PawnSensingComponent->SetPeripheralVisionAngle(20.f);
	PawnSensingComponent->SightRadius = 1000.f;
	
	
	

	
}


// Called when the game starts or when spawned
void AAIBase::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AAIBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	
	
}

// Called to bind functionality to input
void AAIBase::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

