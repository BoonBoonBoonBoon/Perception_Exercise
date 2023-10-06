// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/SphereComponent.h"
#include "GameFramework/Character.h"
#include "PreyAIPawn.generated.h"

UCLASS()
class PERCEPTION_API APreyAIPawn : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	APreyAIPawn();

	// Radius for enemies nearby
	UPROPERTY(EditAnywhere,Category=Tracers)
	class USphereComponent* RadiusSphere;

	UFUNCTION( )
	void OnOverlapBegin(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, 
	int32 OtherBodyIndex, bool bFromSweep, const FHitResult &SweepResult );

	UFUNCTION()
	void OnOverlapEnd(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, 
	int32 OtherBodyIndex, bool bFromSweep, const FHitResult &SweepResult);
	
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
	
	// Checks 
	bool bSeePredator;

protected:

	// SphereLineTraces

	// Height of sphere starting from location of the actor
	UPROPERTY(EditAnywhere,Category="Sweep")
	float SphereHeight = 200;

	// Raidus of the sphere trace
	UPROPERTY(EditAnywhere,Category="Sweep")
	float SphereRadius = 500;

	// How many segements are apart of the sphere - visual
	UPROPERTY(EditAnywhere,Category="Sweep")
	int32 Segements = 12;
	
	void SetupSphere();

	
};
