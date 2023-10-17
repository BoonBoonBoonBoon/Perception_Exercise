// Fill out your copyright notice in the Description page of Project Settings.


#include "BaseAI/MyBTTask_AvoidPlayer.h"

#include "AIController.h"
#include "NavigationSystem.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Perception/PerceptionCharacter.h"

EBTNodeResult::Type UMyBTTask_AvoidPlayer::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	
	AAIController* AIController = Cast<AAIController>(OwnerComp.GetAIOwner());
	if (!AIController)
	{
		return EBTNodeResult::Failed;
	}

	// Get blackboard keys
	FVector AILocation = AIController->GetPawn()->GetActorLocation();
	FVector OtherAILocation = GetBlackboardComponent()->GetValueAsVector(GetSelectedBlackboardKey());

	// Calculate the distance to the other AI
	float DistanceToOtherAI = FVector::Dist(AILocation, OtherAILocation);

	if (DistanceToOtherAI < AcceptanceRadius)
	{
		// Calculate a new target location to avoid the other AI
		FVector Direction = (AILocation - OtherAILocation).GetSafeNormal();
		FVector NewTargetLocation = OtherAILocation + Direction * AcceptanceRadius;

		// Find a random point within a radius around the adjusted target location
		UNavigationSystemV1* NavSystem = FNavigationSystem::GetCurrent<UNavigationSystemV1>(GetWorld());
		if (NavSystem)
		{
			FNavLocation RandomLocation;
			if (NavSystem->GetRandomPointInNavigableRadius(NewTargetLocation, AcceptanceRadius, RandomLocation))
			{
				// Move the AI towards the random location
				AIController->MoveToLocation(RandomLocation.Location);
				return EBTNodeResult::InProgress;
			}
		}
	}

	
	// finish task if succeeded 
	FinishLatentTask(OwnerComp, EBTNodeResult::Succeeded);
	return Super::ExecuteTask(OwnerComp, NodeMemory);
}

void UMyBTTask_AvoidPlayer::MaintainDistanceFromObject(const AActor* ActorToMaintainDistanceFrom, float DesiredDistance)
{
	if (!ActorToMaintainDistanceFrom)
	{
		// Handle the case where the object is not valid
		return;
	}
	
	// Get the AI character's location
	FVector AILocation = GetActorLocation();

	// Get the object's location
	FVector ObjectLocation = ActorToMaintainDistanceFrom->GetActorLocation();

	// Calculate the distance to the object
	float DistanceToObject = FVector::Dist(AILocation, ObjectLocation);

	if (DistanceToObject < DesiredDistance)
	{
		// Calculate a new target location at the desired distance from the object
		FVector Direction = (AILocation - ObjectLocation).GetSafeNormal();
		FVector NewTargetLocation = ObjectLocation + Direction * DesiredDistance;

		// Find a random point within a radius around the adjusted target location
		UNavigationSystemV1* NavSystem = FNavigationSystem::GetCurrent<UNavigationSystemV1>(GetWorld());
		if (NavSystem)
		{
			FNavLocation RandomLocation;
			if (NavSystem->GetRandomPointInNavigableRadius(NewTargetLocation, DesiredDistance, RandomLocation))
			{
				// Move the AI character towards the random location
				UNavigationSystemV1::SimpleMoveToLocation(GetController(), RandomLocation.Location);
			}
		}
	}
}

FString UMyBTTask_AvoidPlayer::GetStaticDescription() const
{
	return FString::Printf(TEXT("Vector %s"), *BlackboardKey.SelectedKeyName.ToString());
}

UMyBTTask_AvoidPlayer::UMyBTTask_AvoidPlayer()
{
	NodeName = "Avoid Player Task";
	BlackboardKey.AddVectorFilter(this, GET_MEMBER_NAME_CHECKED(UMyBTTask_AvoidPlayer, BlackboardKey));
	
}
