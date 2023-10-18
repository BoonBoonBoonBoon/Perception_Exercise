// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/Tasks/BTTask_BlackboardBase.h"
#include "MyBTTask_AvoidPlayer.generated.h"

/**
 * 
 */
UCLASS()
class PERCEPTION_API UMyBTTask_AvoidPlayer : public UBTTask_BlackboardBase
{
	GENERATED_BODY()
public:
	// Execute task function
	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;

	// Keep Distance from object 
	void MaintainDistanceFromObject(const AActor* ActorToMaintainDistanceFrom, float DesiredDistance);
	
	// Gives node a name
	virtual FString GetStaticDescription() const override;

	UMyBTTask_AvoidPlayer();
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Avoid", meta=(AllowPrivateAccess=true))
	float AvoidDistance = 500.f;

	class AChaseAiController* PredatorCont;
};
