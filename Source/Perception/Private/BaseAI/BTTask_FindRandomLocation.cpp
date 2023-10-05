// Fill out your copyright notice in the Description page of Project Settings.


#include "BaseAI/BTTask_FindRandomLocation.h"

#include "AIController.h"
#include "NavigationSystem.h"
#include "BaseAI/PreyAI/PreyAIPawn.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "GameFramework/CharacterMovementComponent.h"

// Execute is the logic thats created in the normal bps 
EBTNodeResult::Type UBTTask_FindRandomLocation::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	// find location pass it and store it as a vector
	// Empty initializer 
	FNavLocation Location{};

	// Get the ai pawn* Grab the Ai controller of the owner component, which is one of the params being passed in
	AAIController* AiController = OwnerComp.GetAIOwner();
	const APawn* AIPawn = AiController->GetPawn();

	// Get Pawn Origin
	const FVector Origin = AIPawn->GetActorLocation();

	// Obtain the navigation system and find a random location
	const UNavigationSystemV1* NavSystem = UNavigationSystemV1::GetCurrent(GetWorld());
	if(IsValid(NavSystem) && NavSystem->GetRandomPointInNavigableRadius(Origin, SearchRadius, Location))
	{
		// Setting value as vector, vector is the location
		// BlackBoardKey Selector is a struct it hold Name, type, ID and a bool
		// Finding a blackboard key by name and setting its value as a vector 
		AiController->GetBlackboardComponent()->SetValueAsVector(BlackboardKey.SelectedKeyName, Location.Location);
	}

	//Signal the behaviorTreeComponent that the task has finished with success
	// Finishes the task without it, it will continue running or whatever 
	FinishLatentTask(OwnerComp, EBTNodeResult::Succeeded);
	
	return EBTNodeResult::Succeeded;
	
}

// Sets up on the node the variable underline, without it you wont be able to see it
// basically a description on the node 
FString UBTTask_FindRandomLocation::GetStaticDescription() const
{
	return FString::Printf(TEXT("Vector %s"), *BlackboardKey.SelectedKeyName.ToString());
	
	
}


UBTTask_FindRandomLocation::UBTTask_FindRandomLocation()
{
	// Gives node name, What we see on bp node
	NodeName = "Find Random Location in NavMesh";

	// Accept only vectors, since the blackboard key only takes vectors as a data type
	// This says that is filters only for vectors and nothing else for the task * IE. SetValueVector
	BlackboardKey.AddVectorFilter(this, GET_MEMBER_NAME_CHECKED(UBTTask_FindRandomLocation, BlackboardKey));
	
}
