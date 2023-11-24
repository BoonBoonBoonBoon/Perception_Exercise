// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GenericTeamAgentInterface.h"
#include "GameFramework/Character.h"
#include "InputActionValue.h"
#include "Components/SphereComponent.h"
#include "PerceptionCharacter.generated.h"


UCLASS(config=Game)
class APerceptionCharacter : public ACharacter, public IGenericTeamAgentInterface

{
	GENERATED_BODY()

	/** Camera boom positioning the camera behind the character */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	class USpringArmComponent* CameraBoom;

	/** Follow camera */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	class UCameraComponent* FollowCamera;
	
	/** MappingContext */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	class UInputMappingContext* DefaultMappingContext;

	/** Jump Input Action */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	class UInputAction* JumpAction;

	/** Move Input Action */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	class UInputAction* MoveAction;

	/** Look Input Action */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	class UInputAction* LookAction;

	UPROPERTY(EditAnywhere)
	USphereComponent* Collision;
public:
	APerceptionCharacter();
	// Creates Sphere


	/***  Perception Components   ***/
	
	// Used as a generator for the pawn to emit a stimuli. Need this as the AI will use this as a tool to percept.
	class UAIPerceptionStimuliSourceComponent* StimuliSource;
	void SetupStimulusSource();

	// The function that plays the sound (USound is the class that's responsible for playable sound object)
	UFUNCTION(BlueprintCallable, Category=AI)
	void ReportNoise(USoundBase* SoundToPlay, float Volume);

	// Emitter component used to emit the sound to nearby ai.
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UPawnNoiseEmitterComponent* NoiseEmitter;

	// Use it to change the volume from crouching to running to sprinting
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category=Volume)
	float VolumeOutput;

	// Give character an ID and returns the ID
	FGenericTeamId TeamId;
	virtual FGenericTeamId GetGenericTeamId() const override {return FGenericTeamId(TeamId);};

	void MoveForward(float value);
	void MoveSide(float Value);

	
	UPROPERTY(EditAnywhere,BlueprintReadWrite)
	bool bCrouching;

	void StartCrouch();
	void StopCrouch();

	void Health();
protected:

	// Overlap Function
	UFUNCTION()
	virtual void OnOverlapBegin(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
		UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);
	
	/** Called for movement input */
	void Move(const FInputActionValue& Value);

	/** Called for looking input */
	void Look(const FInputActionValue& Value);
			

protected:
	// APawn interface
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
	
	// To add mapping context
	virtual void BeginPlay();

	virtual void Tick(float DeltaSeconds) override;

public:
	/** Returns CameraBoom subject **/
	FORCEINLINE class USpringArmComponent* GetCameraBoom() const { return CameraBoom; }
	/** Returns FollowCamera subject **/
	FORCEINLINE class UCameraComponent* GetFollowCamera() const { return FollowCamera; }
};

