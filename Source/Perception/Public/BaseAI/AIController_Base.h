// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BaseAI/Perception/BasicPerceptionComponent.h"
#include "AIController.h"
#include "Perception/AIPerceptionTypes.h"
#include "BehaviorTree/BehaviorTreeComponent.h"
#include "AIController_Base.generated.h"

/**
 * 
 */
UCLASS()
class PERCEPTION_API AAIController_Base : public AAIController
{
	GENERATED_BODY()
public:

	explicit AAIController_Base(FObjectInitializer const& ObjectInitializer);

	
	// Configuration for senses under perception class 
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Sight Config")
	UAISenseConfig_Sight* SightConfig;

	/*UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Hearing Perception")
	UAISenseConfig_Hearing* HearingConfig;*/

	void SetupPerceptionSystem();

	UFUNCTION()
	void OnTargetDetected(AActor* Actor, FAIStimulus const Stimulus);


protected:
	virtual void BeginPlay() override;
	
	// When Ai is Possessed  
	virtual void OnPossess(APawn* InPawn) override;

	
private:

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "AI", meta = (AllowPrivateAccess = true))
	TObjectPtr<UBehaviorTree> BehaviorTree;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "AI", meta = (AllowPrivateAccess = true))
	TObjectPtr<UBehaviorTreeComponent> BehaviorTreeComponent;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "AI", meta = (AllowPrivateAccess = true))
	UBlackboardComponent* BlackboardComponent;

	UPROPERTY(EditAnywhere)
	UAIPerceptionComponent* PerceptionComp;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Perception", meta=(AllowPrivateAccess=true))
	TObjectPtr<UBasicPerceptionComponent> Perception;
};
