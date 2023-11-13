// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "ChaseAI.generated.h"

UCLASS()
class PERCEPTION_API AChaseAI : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AChaseAI();

	UFUNCTION( )
	void OnOverlapBegin(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, 
	int32 OtherBodyIndex, bool bFromSweep, const FHitResult &SweepResult );

	UFUNCTION()
	void OnOverlapEnd(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, 
	int32 OtherBodyIndex, bool bFromSweep, const FHitResult &SweepResult);
	
	// Used as a generator for the pawn to emit a stimuli. Need this as the AI will use this as a tool to percept.
	class UAIPerceptionStimuliSourceComponent* StimuliSourcePredator;
	void SetupStimulusSource();

	// The function that plays the sound (USound is the class that's responsible for playable sound object)
	UFUNCTION(BlueprintCallable, Category=AI)
	void ReportNoise(USoundBase* SoundToPlay, float Volume);

	// Emitter component used to emit the sound to nearby ai.
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UPawnNoiseEmitterComponent* NoiseEmitter;


	void MoveToWaypoints();
	
	// Get the current waypoint
	UPROPERTY(EditAnywhere, meta = (AllowPrivateAccess = "True"))
	int CurrentWaypoint;
	
	// Initialize Waypoints
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Waypoints")
	TArray<AActor*> Waypoints;
	
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

};
