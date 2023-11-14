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

	void TestDistFunc();




	UFUNCTION( )
	void OnOverlapBegin(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, 
	int32 OtherBodyIndex, bool bFromSweep, const FHitResult &SweepResult );

	UFUNCTION()
	void OnOverlapEnd(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, 
	int32 OtherBodyIndex, bool bFromSweep, const FHitResult &SweepResult);
	
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	// Used as a generator for the pawn to emit a stimuli. Need this as the AI will use this as a tool to percept.
	class UAIPerceptionStimuliSourceComponent* StimuliSourcePrey;
	void SetupStimulusSource();

	// The function that plays the sound (USound is the class that's responsible for playable sound object)
	UFUNCTION(BlueprintCallable, Category=AI)
	void ReportNoise(USoundBase* SoundToPlay, float Volume);

	// Emitter component used to emit the sound to nearby ai.
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UPawnNoiseEmitterComponent* NoiseEmitter;
	
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
