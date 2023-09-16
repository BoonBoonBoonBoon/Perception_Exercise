// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "ChaseAiController.h"
#include "BehaviorTree/Tasks/BTTask_BlackboardBase.h"
#include "BTTask_ChasePrey.generated.h"

/**
 * 
 */
UCLASS()
class PERCEPTION_API UBTTask_ChasePrey : public UBTTask_BlackboardBase
{
	GENERATED_BODY()
public:

	UPROPERTY()
	AChaseAiController* Controller;
	
	// Executes the task, Stores all the logic needed. 
	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;

	// Underline Descriptive part of the node. 
	virtual FString GetStaticDescription() const override;

	// Constuctor
	UBTTask_ChasePrey();

protected:

	/*UPROPERTY()
	float MovementRadius = 1000.f; 
	*/
	
	
private:
	
	
};
