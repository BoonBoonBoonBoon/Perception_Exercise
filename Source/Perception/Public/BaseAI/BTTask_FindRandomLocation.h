// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AIController_Base.h"
#include "BehaviorTree/Tasks/BTTask_BlackboardBase.h"
#include "BTTask_FindRandomLocation.generated.h"

/**
 *  Finding random location on a navmesh
 */
UCLASS()
class PERCEPTION_API UBTTask_FindRandomLocation : public UBTTask_BlackboardBase
{
	GENERATED_BODY()

public:

	UPROPERTY()
	AAIController_Base* Controller;
	
	// Execute task function
	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;
	
	//
	virtual FString GetStaticDescription() const override;
	
	// Contrsuctor 
	UBTTask_FindRandomLocation();

	
private:
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Search", meta=(AllowPrivateAccess=true))
		float SearchRadius = 1500.f;
};
