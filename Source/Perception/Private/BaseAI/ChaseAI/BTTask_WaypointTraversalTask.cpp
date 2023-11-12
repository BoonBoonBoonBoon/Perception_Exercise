// Fill out your copyright notice in the Description page of Project Settings.


#include "BaseAI/ChaseAI/BTTask_WaypointTraversalTask.h"
#include "BaseAI/ChaseAI/ChaseAiController.h"
#include "GameFramework/Actor.h"
#include "NavigationSystem.h"
#include "BehaviorTree/Blackboard/BlackboardKeyType_Object.h"

UBTTask_WaypointTraversalTask::UBTTask_WaypointTraversalTask()
{
	NodeName = "AStarWaypointTraversalTask";
}

EBTNodeResult::Type UBTTask_WaypointTraversalTask::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	return Super::ExecuteTask(OwnerComp, NodeMemory);
}
