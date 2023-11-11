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
UCLASS()
class PERCEPTION_API ANoiseTrapController : public AAIController, public IAISightTargetInterface
{
	GENERATED_BODY()

public:
	
	ANoiseTrapController(FObjectInitializer const& ObjectInitializer);
	
	virtual void BeginPlay() override;

	void setupInit();
	
	UFUNCTION()
	void OnTargetDetected(AActor* Actor, FAIStimulus Stimulus);
	
	// Pawn on possess	
	virtual void OnPossess(APawn* InPawn) override;

protected:
	//DBA
	FGenericTeamId TeamId;
	
	virtual ETeamAttitude::Type GetTeamAttitudeTowards(const AActor& Other) const override;

public:
	virtual FGenericTeamId GetGenericTeamId() const override {return TeamId;};

	UPROPERTY(EditAnywhere)
	class ANoiseTrapAI* Agent;
	
	
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
