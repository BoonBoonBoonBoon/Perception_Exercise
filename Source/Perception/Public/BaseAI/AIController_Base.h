// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AIBase_PawnSensingComponent.h"
#include "AIController.h"
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

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Sensing", meta=(AllowPrivateAccess=true))
	TObjectPtr<UAIBase_PawnSensingComponent> Perception;
};
