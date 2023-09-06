// Fill out your copyright notice in the Description page of Project Settings.


#include "BaseAI/MyBTTask_AvoidPlayer.h"

#include "AIController.h"
#include "NavigationSystem.h"
#include "BehaviorTree/BlackboardComponent.h"

EBTNodeResult::Type UMyBTTask_AvoidPlayer::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{

	FNavLocation Location{};

	
	AAIController* AiController = OwnerComp.GetAIOwner();
	const APawn* AIPawn = AiController->GetPawn();
	const FVector Origin = AIPawn->GetActorLocation();

	//
	const UNavigationSystemV1* NavSystem = UNavigationSystemV1::GetCurrent(GetWorld());
	if(IsValid(NavSystem) && NavSystem->GetRandomPointInNavigableRadius(Origin, AvoidDistance, Location))
	{
		AiController->GetBlackboardComponent()->SetValueAsVector(BlackboardKey.SelectedKeyName, Location.Location);
	}
	
	return Super::ExecuteTask(OwnerComp, NodeMemory);
}

FString UMyBTTask_AvoidPlayer::GetStaticDescription() const
{
	return FString::Printf(TEXT("Vector %s"), *BlackboardKey.SelectedKeyName.ToString());
}

UMyBTTask_AvoidPlayer::UMyBTTask_AvoidPlayer()
{
	NodeName = "Avoid Player";
	
	
}
