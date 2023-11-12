// Fill out your copyright notice in the Description page of Project Settings.


#include "BaseAI/ChaseAI/BTTask_WaypointTraversalTask.h"
#include "BaseAI/ChaseAI/ChaseAiController.h"
#include "GameFramework/Actor.h"
#include "NavigationSystem.h"
#include "NavigationPath.h"
#include "NavigationData.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "BehaviorTree/Blackboard/BlackboardKeyType_Object.h"

UBTTask_WaypointTraversalTask::UBTTask_WaypointTraversalTask()
{
	NodeName = "AStarWaypointTraversalTask";
}

EBTNodeResult::Type UBTTask_WaypointTraversalTask::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{

	AChaseAiController* Controller = Cast<AChaseAiController>(OwnerComp.GetAIOwner());
	if (Controller)
	{
		// Get the current waypoint actor from the blackboard
		AActor* CurrentWaypointActor = Cast<AActor>(OwnerComp.GetBlackboardComponent()->GetValueAsObject(WaypointKey));
		if (CurrentWaypointActor)
		{
			// Get the AI's location and the target waypoint's location
			FVector StartLocation = Controller->GetPawn()->GetActorLocation();
			FVector EndLocation = CurrentWaypointActor->GetActorLocation();

			// Use A* algorithm to find a path
			UNavigationSystemV1* NavSys = FNavigationSystem::GetCurrent<UNavigationSystemV1>(Controller);
			if (NavSys)
			{
				UNavigationPath* NavPath = NavSys->FindPathToLocationSynchronously(Controller, StartLocation, EndLocation);
				if (NavPath && NavPath->IsValid())
				{
					// Move the AI along the A* path using your movement logic
					//Controller->MoveOnPath(NavPath);

					return EBTNodeResult::InProgress; // Assuming the task takes time to complete
				}
			}
		}
	}
	return EBTNodeResult::Failed;
}