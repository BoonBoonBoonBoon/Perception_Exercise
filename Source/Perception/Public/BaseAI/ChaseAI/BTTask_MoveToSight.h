// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/Tasks/BTTask_BlackboardBase.h"
#include "BTTask_MoveToSight.generated.h"

/**
 * 
 */
UCLASS()
class PERCEPTION_API UBTTask_MoveToSight : public UBTTask_BlackboardBase
{
	GENERATED_BODY()

	UBTTask_MoveToSight();

	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;
	
};
