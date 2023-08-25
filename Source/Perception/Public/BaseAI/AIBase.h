// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BehaviorTree.h"
#include "BaseAI\AIBase_PawnSensingComponent.h"
#include "GameFramework/Character.h"
#include "BaseAI/CustomSensing/CustomPawnSensing.h"
#include "AIBase.generated.h"


UCLASS()
class PERCEPTION_API AAIBase : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AAIBase();
	
	UPROPERTY(EditAnywhere,BlueprintReadWrite, Category="Body")
	UStaticMeshComponent* Body;

	UPROPERTY(EditAnywhere,BlueprintReadWrite, Category="Head")
	UStaticMeshComponent* Head;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Sensing")
	UCustomPawnSensing* PawnSensing;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="DetectionBody")
	USphereComponent*DetectionBody;


	void OnBeginOverlap(UPrimitiveComponent* OverlapComponent, 
	AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, 
	bool bFromSweep, const FHitResult& SweepResult);

	
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;


	
public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
	
};
