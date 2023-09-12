// Fill out your copyright notice in the Description page of Project Settings.

#pragma once


#include "CoreMinimal.h"
#include "AIController.h"
#include "BehaviorTree/BehaviorTreeComponent.h"
#include "Perception/AIPerceptionComponent.h"
#include "Perception/AISenseConfig_Sight.h"
#include "GameFramework/Controller.h"
#include "PreyController.generated.h"

/**
 * 
 */
UCLASS()
class PERCEPTION_API APreyController : public AAIController
{
	GENERATED_BODY()
	
public:

	// Constructor
	explicit APreyController(FObjectInitializer const& ObjectInitializer);

	// Set up the forward init
	void SetupPerception();

	// if param are true, set boolean for ai to flee.
	UFUNCTION()
	void OnTargetDetected(AActor* Actor, FAIStimulus const Stimulus);
	
	/** Returns the seeing pawn. Returns null, if our AI has no target */
	AActor* GetSeeingPawn();
	
protected:
	virtual void BeginPlay() override;
	
	// When Ai is Possessed  
	virtual void OnPossess(APawn* InPawn) override;

	const FName BBEnemyKey = FName("Enemy");


	// Configuration for senses under perception class 
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Sight Config")
	UAISenseConfig_Sight* SightConfig;
	
private:
	
	// Start Contains the logic
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "AI", meta = (AllowPrivateAccess = true))
	TObjectPtr<UBehaviorTree> BehaviorTree;
	
	// To start the BT
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "AI", meta = (AllowPrivateAccess = true))
	TObjectPtr<UBehaviorTreeComponent> BehaviorTreeComponent;

	// Initialize the bb values && set/get
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "AI", meta = (AllowPrivateAccess = true))
	UBlackboardComponent* BlackboardComponent;

	// Perception of the ai
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Perception", meta=(AllowPrivateAccess=true))
	TObjectPtr<UAIPerceptionComponent> PerceptionComp;
	
	
	
};