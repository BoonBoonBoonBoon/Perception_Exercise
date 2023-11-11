// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/Tasks/BTTask_BlackboardBase.h"
#include "WaypointNavigationTask.generated.h"

/**
 * 
 */
UCLASS()
class PERCEPTION_API UWaypointNavigationTask : public UBTTask_BlackboardBase
{
	GENERATED_BODY()

public:
	UWaypointNavigationTask();

	virtual FString GetStaticDescription() const override;
	
protected:
	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;
};
