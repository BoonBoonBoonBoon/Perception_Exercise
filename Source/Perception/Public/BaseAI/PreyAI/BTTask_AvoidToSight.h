// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/Tasks/BTTask_BlackboardBase.h"
#include "BTTask_AvoidToSight.generated.h"

/**
 * 
 */
UCLASS()
class PERCEPTION_API UBTTask_AvoidToSight : public UBTTask_BlackboardBase
{
	GENERATED_BODY()
	
	UBTTask_AvoidToSight();

	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;

	FVector CalulateAvoidanceLocation(AAIController* AIController, AActor* DetecedActor);
	
};
