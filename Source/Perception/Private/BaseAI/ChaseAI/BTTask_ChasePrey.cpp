// Fill out your copyright notice in the Description page of Project Settings.


#include "BaseAI/ChaseAI/BTTask_ChasePrey.h"

EBTNodeResult::Type UBTTask_ChasePrey::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	return Super::ExecuteTask(OwnerComp, NodeMemory);
/*
 *	Watch EBTNodeResults (4 Types of return).
 *	Succeeded. Failed. Aborted. InProgress.
 */

	
}

FString UBTTask_ChasePrey::GetStaticDescription() const
{
	
	// Sets up on the node the variable underline, without it you wont be able to see it. I.E (Vector TargetLocation)
	// LastPart Looks for the selected key that w have assigned, I.E, TargetLoc or HidingSpot E.T.C.
	return FString::Printf(TEXT("Vector %s"), *BlackboardKey.SelectedKeyName.ToString());
}

UBTTask_ChasePrey::UBTTask_ChasePrey()
{

	// Name of the actual Node.
	NodeName = "Chase Prey";

	// (Filter)
	

	
	
}
