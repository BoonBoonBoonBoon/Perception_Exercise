// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/Tasks/BTTask_BlackboardBase.h"
#include "BTTask_MoveToNoise.generated.h"

/**
 * 
 */
UCLASS()
class PERCEPTION_API UBTTask_MoveToNoise : public UBTTask_BlackboardBase
{
	GENERATED_BODY()

public:
	UBTTask_MoveToNoise();

	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;
	
};
