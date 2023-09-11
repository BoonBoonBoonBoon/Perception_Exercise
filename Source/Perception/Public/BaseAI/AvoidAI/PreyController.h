// Fill out your copyright notice in the Description page of Project Settings.

#pragma once


#include "CoreMinimal.h"
#include "AIController.h"
#include "BehaviorTree/BehaviorTreeComponent.h"
#include "Perception/AIPerceptionComponent.h"
#include "Perception/AISenseConfig_Sight.h"
#include "PreyController.generated.h"

/**
 * 
 */
UCLASS()
class PERCEPTION_API APreyController : public AAIController
{
	GENERATED_BODY()
	
public:
	// Used to init values and set/get values from bb asset
	UBlackboardComponent* BlackboardComp;

	// Used to start BT
	UBehaviorTreeComponent* BehaviorTreeComp;

	// bb key value name
	const FName BlackboardEnemyKey = FName("Enemy");

	// Function fires when Perception gets updated 
	UFUNCTION()
	void OnPerceptionUpdated(TArray<AActor*> UpdatedActors);

	// Sight Sense Config
	UAISenseConfig_Sight* Sight;

protected:

	// BT that contains logic for ai
	UPROPERTY(EditAnywhere)
	UBehaviorTree* BehaviorTree;

	// Perception Component of AI
	UPROPERTY(EditAnywhere)
	UAIPerceptionComponent* AiPerceptionComponent;

public:

	APreyController();

	virtual void OnPossess(APawn* InPawn) override;

	// Retunrs the seeing pawn. returns null if no  target
	AActor* GetSeeingPawn();
};
