// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "PreyAIPawn.generated.h"

UCLASS()
class PERCEPTION_API APreyAIPawn : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	APreyAIPawn();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	bool bSeePredator;
	
};
