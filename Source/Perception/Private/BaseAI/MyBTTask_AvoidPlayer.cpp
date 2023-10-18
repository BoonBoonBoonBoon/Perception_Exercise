// Fill out your copyright notice in the Description page of Project Settings.


#include "BaseAI/MyBTTask_AvoidPlayer.h"

#include "AIController.h"
#include "NavigationSystem.h"
#include "BaseAI/ChaseAI/ChaseAiController.h"
#include "BaseAI/PreyAI/AIPreyController.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Perception/PerceptionCharacter.h"

EBTNodeResult::Type UMyBTTask_AvoidPlayer::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{

	
	// Cast Controller to the controller we want to use
	// Might be wrong 
	AAIController* AIController = Cast<AAIPreyController>(OwnerComp.GetAIOwner());
	if (!AIController)
	{
		// Cancel Task 
		return EBTNodeResult::Failed;
	}

	// Get the AI's location
	const FVector CurrentAILoc = AIController->GetPawn()->GetActorLocation();

	// V---Come back and make sure that DBA is on and can only detect enemies and not those who pose a threat---V

	//The issue is here --V  
	FVector OtherAILocation = PredatorCont->GetBlackboardComponent()->GetValueAsVector(GetSelectedBlackboardKey());

	// Calc the dist between current ai to the other AI
	float DistanceToOtherAI = FVector::Dist(CurrentAILoc, OtherAILocation);
	
	
	// If the distance to the other ai is below the safe distance 
	if (DistanceToOtherAI < AvoidDistance)
	{
		// Calculate a new target location to avoid the other AI
		FVector Direction = (CurrentAILoc - OtherAILocation).GetSafeNormal();
		FVector NewTargetLocation = OtherAILocation + Direction * AvoidDistance;

		// Find a random point within a radius around the adjusted target location
		UNavigationSystemV1* NavSystem = FNavigationSystem::GetCurrent<UNavigationSystemV1>(GetWorld());
		if (NavSystem)
		{
			FNavLocation RandomLocation;
			if (NavSystem->GetRandomPointInNavigableRadius(NewTargetLocation, AvoidDistance, RandomLocation))
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
	/*if (!ActorToMaintainDistanceFrom)
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
	}*/
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
