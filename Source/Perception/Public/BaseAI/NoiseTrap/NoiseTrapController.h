// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "NoiseTrapAI.h"
#include "BehaviorTree/BehaviorTreeComponent.h"
#include "Perception/AISenseConfig_Hearing.h"
#include "Perception/AISenseConfig_Sight.h"
#include "Perception/AISightTargetInterface.h"
#include "NoiseTrapController.generated.h"

/**
 * 
 */
UCLASS(Blueprintable)
class PERCEPTION_API ANoiseTrapController : public AAIController, public IAISightTargetInterface
{
	GENERATED_BODY()

public:

	// Consturctor
	ANoiseTrapController(FObjectInitializer const& ObjectInitializer);

	// Begin Play
	virtual void BeginPlay() override;

	// Setup Senses
	void setupInit();

	// How to react to target
	UFUNCTION()
	void OnTargetDetected(AActor* Actor, FAIStimulus Stimulus);
	
	// Pawn on possess	
	virtual void OnPossess(APawn* InPawn) override;


	//** Detection By Affiliation **// 
	
	// Assigns the Controller an id variable
	FGenericTeamId TeamId;

	// Returns Team ID
	virtual FGenericTeamId GetGenericTeamId() const override {return TeamId;};

	// Assign Teams and Reactions
	virtual ETeamAttitude::Type GetTeamAttitudeTowards(const AActor& Other) const override;
	
	UPROPERTY(EditAnywhere)
	class ANoiseTrapAI* Agent;

	// Event for when the AI spots the player 
	/*
	UFUNCTION(BlueprintCallable, Category="Noise")
	void MakeNoise(float Loudness);
	*/

	
	//** Perception Components **// 
	
	// Behaviour Tree and Blackboard Components
	UPROPERTY(EditAnywhere)
	TObjectPtr<UBehaviorTree> BT;

	UPROPERTY(EditAnywhere)
	TObjectPtr<UBehaviorTreeComponent> BTComp;

	UPROPERTY(EditAnywhere)
	TObjectPtr<UBlackboardComponent> BBComp;

	// Perception Components && Sense Configs  
	UPROPERTY(EditAnywhere)
	TObjectPtr<UAIPerceptionComponent> PerceptionComp;
	
	UPROPERTY(EditAnywhere)
	TObjectPtr<UAISenseConfig_Hearing> Config_Hearing;

	UPROPERTY(EditAnywhere)
	TObjectPtr<UAISenseConfig_Sight> Config_Sight;

	// Blackboard key for hearing the player 
	const FName BBHearPlayerKey = FName("HearPlayer");
	
	// Blackboard key for seeing the player
	const FName BBSeePlayerKey = FName("SeePlayer");
};
