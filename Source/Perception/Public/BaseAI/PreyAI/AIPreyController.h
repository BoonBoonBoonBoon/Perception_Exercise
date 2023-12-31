// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "PreyAIPawn.h"
#include "BehaviorTree/BehaviorTreeComponent.h"
#include "EnvironmentQuery/EnvQuery.h"
#include "Perception/AISenseConfig_Damage.h"
#include "Perception/AISenseConfig_Hearing.h"
#include "Perception/AISenseConfig_Prediction.h"
#include "Perception/AISenseConfig_Team.h"
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

	UPROPERTY(EditAnywhere)
	FGenericTeamId TeamId;
	
	// Returns Team ID
	virtual FGenericTeamId GetGenericTeamId() const override {return TeamId;};

	// Assign Teams and Reactions
	virtual ETeamAttitude::Type GetTeamAttitudeTowards(const AActor& Other) const override;
	
	// Boolean used to check if actor should react (Check BTTask MoveToNoise)
	bool ShouldReactToNoise(AActor* NoiseInstigator) const;

	// Boolean used to check if actor should react (Check BTTask MoveToSight
	bool ShouldReactToSight(AActor* SightInstigator) const;






	
protected:
	// EQS
	UPROPERTY(EditAnywhere, Category="AI")
	UEnvQuery* EnvQuery;

	// Array for each actor
	TArray<APreyAIPawn> PreyAIPawns;

	class APreyAIPawn* PreyAIPawn;
	
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
	TObjectPtr<UAISenseConfig_Prediction> Config_Prediction;

	UPROPERTY(EditAnywhere)
	TObjectPtr<UAISenseConfig_Damage> Config_Damage;

	UPROPERTY(EditAnywhere)
	TObjectPtr<UAISenseConfig_Team> Config_Team;
	
	UPROPERTY(EditAnywhere)
	TObjectPtr<UAIPerceptionComponent> PerceptionComp;

	
public:

	// Assigns a new blackboard key
	const FName BBSeePredatorKey = FName("SeePredator");

	const FName BBHearPredatorKey = FName("HearPredator");

	// Ai Statistics

	// Health
	float DefaultHealth;
	float CurrentHealth;
	float Damage;
	bool bHasBeenHit;

	// Speed 
	float DefaultSpeed = 250;
	float MaxSpeed = 600;
	float DamagedSpeed = 350;

	
	bool Alert;
	bool Calm;
	
	
};
