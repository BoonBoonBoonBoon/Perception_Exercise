// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "BehaviorTree/BehaviorTreeComponent.h"
#include "EnvironmentQuery/EnvQuery.h"
#include "Perception/AISenseConfig_Hearing.h"
#include "Perception/AISense_Sight.h"
#include "AIPreyController.generated.h"

/**
 * 
 */
UCLASS()
class PERCEPTION_API AAIPreyController : public AAIController
{
	GENERATED_BODY()

public:

	AAIPreyController(FObjectInitializer const& ObjectInitializer);

	virtual void BeginPlay() override;

	void setupInit();
	
	UFUNCTION()
	void OnTargetDetected(AActor* Actor, FAIStimulus Stimulus);
	
	// Pawn on possess	
	virtual void OnPossess(APawn* InPawn) override;
	
protected:
	// EQS
	UPROPERTY(EditAnywhere, Category="AI")
	UEnvQuery* EnvQuery;

	
	// Behaviour tree & Blackboard
	
	UPROPERTY(EditAnywhere)
	TObjectPtr<UBehaviorTree> BT;

	UPROPERTY(EditAnywhere)
	TObjectPtr<UBehaviorTreeComponent> BTComp;

	UPROPERTY(EditAnywhere)
	TObjectPtr<UBlackboardComponent> BBComp;

	// Perception Components

	UPROPERTY(EditAnywhere)
	TObjectPtr<UAISenseConfig_Hearing> Config_Hearing;

	UPROPERTY(EditAnywhere)
	TObjectPtr<UAISenseConfig_Sight> Config_Sight;
	
	UPROPERTY(EditAnywhere)
	TObjectPtr<UAIPerceptionComponent> PerceptionComp;

	
public:

	// Assigns a new blackboard key
	const FName BBPredatorKey = FName("Predator");

	const FName BBHearPlayerKey = FName("HearPlayer");

	const FName BBHearPredatorKey = FName("HearPredator");


	
};
