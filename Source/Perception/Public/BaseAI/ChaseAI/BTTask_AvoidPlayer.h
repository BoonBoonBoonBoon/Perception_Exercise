// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "ChaseAiController.h"
#include "BehaviorTree/Tasks/BTTask_BlackboardBase.h"
#include "BTTask_AvoidPlayer.generated.h"

/**
 * 
 */
UCLASS()
class PERCEPTION_API UBTTask_AvoidPlayer : public UBTTask_BlackboardBase
{
	GENERATED_BODY()

public:
	AChaseAiController* Controller;
	
	// Execute task function
	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;
	
	//
	virtual FString GetStaticDescription() const override;
	
	// Contrsuctor 
	UBTTask_AvoidPlayer();
	
};
