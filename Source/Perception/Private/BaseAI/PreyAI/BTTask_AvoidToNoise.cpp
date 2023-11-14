// Fill out your copyright notice in the Description page of Project Settings.


#include "BaseAI/PreyAI/BTTask_AvoidToNoise.h"

UBTTask_AvoidToNoise::UBTTask_AvoidToNoise()
{
}

EBTNodeResult::Type UBTTask_AvoidToNoise::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	return Super::ExecuteTask(OwnerComp, NodeMemory);
}
