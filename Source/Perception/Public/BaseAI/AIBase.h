// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BehaviorTree.h"
#include "BaseAI\AIBase_PawnSensingComponent.h"
#include "GameFramework/Character.h"
#include "AIBase.generated.h"

UCLASS()
class PERCEPTION_API AAIBase : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AAIBase();

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category=Perception, meta=(AllowPrivateAccess=true))
	class UAIBase_PawnSensingComponent* PawnSensingComponent;

	
	
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;


	
public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	
};
