// Fill out your copyright notice in the Description page of Project Settings.


#include "BaseAI/Waypoints/WaypointNavigationTask.h"

#include "BehaviorTree/BlackboardComponent.h"
#include "Perception\Public\BaseAI\ChaseAI\ChaseAiController.h"
#include "Perception/Public/BaseAI/ChaseAI/ChaseAI.h"
#include "Perception\Public\BaseAI\Waypoints\WayPoints.h"

UWaypointNavigationTask::UWaypointNavigationTask()
{
	NodeName = "Move To Waypoint";
}

FString UWaypointNavigationTask::GetStaticDescription() const
{
	return FString::Printf(TEXT("Vector %s"), *BlackboardKey.SelectedKeyName.ToString());
}

EBTNodeResult::Type UWaypointNavigationTask::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	AAIController* CController = OwnerComp.GetAIOwner();
	AChaseAI* ChaseAI = Cast<AChaseAI>(CController->GetPawn());

	if (ChaseAI)
	{
		// Get the current waypoint index from the Blackboard
		int32 CurrentWaypointIndex = OwnerComp.GetBlackboardComponent()->GetValueAsInt(GetSelectedBlackboardKey());

		// Ensure there are waypoints
		if (ChaseAI->Waypoints.Num() == 0)
		{
			UE_LOG(LogTemp, Warning, TEXT("No waypoints set for AI."));
			return EBTNodeResult::Failed;
		}

		// Get the next waypoint
		AActor* NextWaypoint = ChaseAI->Waypoints[CurrentWaypointIndex];

		// Move the AI to the waypoint
		CController->MoveToLocation(NextWaypoint->GetActorLocation(), 5.0f, true, true);

		// Increment the waypoint index
		CurrentWaypointIndex = (CurrentWaypointIndex + 1) % ChaseAI->Waypoints.Num();

		// Set the new waypoint index in the Blackboard
		OwnerComp.GetBlackboardComponent()->SetValueAsInt(GetSelectedBlackboardKey(), CurrentWaypointIndex);
	}

	return EBTNodeResult::Succeeded;
	
	return Super::ExecuteTask(OwnerComp, NodeMemory);
}
