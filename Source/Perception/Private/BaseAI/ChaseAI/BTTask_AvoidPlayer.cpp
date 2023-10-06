// Fill out your copyright notice in the Description page of Project Settings.


#include "BaseAI/ChaseAI/BTTask_AvoidPlayer.h"

#include "NavigationSystem.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Kismet/KismetMathLibrary.h"
#include "Perception/PerceptionCharacter.h"

EBTNodeResult::Type UBTTask_AvoidPlayer::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{

	/*// Assign the controller as the owner of thr BTComp.
	AAIController* AiController = OwnerComp.GetAIOwner();
	// need to assign a pawn to use the controller. 
	const APawn* AIPawn = AiController->GetPawn();
	// Get the starting location of the pawn.
	const FVector Origin = AIPawn->GetActorLocation();
	// Radius pawn can travel.
	const float Radius = 1000.f;
	
	
	const APlayerController* PlayerController = nullptr;
	const APawn* Pawn = PlayerController->GetPawn();
	FVector PlayerLoc = Pawn->GetActorLocation();

	//FVector Avoid = Pawn->GetActorLocation() + Location;
	//UKismetMathLibrary::GetDirectionUnitVector(Pawn, Avoid);
	
	FVector target = Pawn->GetActorLocation();
	FVector CurrentLocation = AIPawn->GetActorLocation();

	FVector direction = target - CurrentLocation;*/







	
	// Empty Struct since we do not have a definitive location.
	FNavLocation Location{};

	// Get the ai pawn* Grab the Ai controller of the owner component, which is one of the params being passed in
	AAIController* AiController = OwnerComp.GetAIOwner();
	const APawn* AIPawn = AiController->GetPawn();

	// Get Pawn Origin
	const FVector Origin = AIPawn->GetActorLocation();

	
	// Refrence for navsystem. Which gets current level. 
	const UNavigationSystemV1* NavSys = UNavigationSystemV1::GetCurrent(GetWorld());

	
	if(IsValid(NavSys) && NavSys->GetRandomReachablePointInRadius(Origin, SearchRadius, ))
	{
		
	}


	
	/*if(IsValid(NavSys) && NavSys->GetRandomReachablePointInRadius(Origin, Radius, Location))
	{
		AiController->GetBlackboardComponent()->SetValueAsVector(BlackboardKey.SelectedKeyName, Location.Location);
	}
	*/
	
	return Super::ExecuteTask(OwnerComp, NodeMemory);
	
}

FString UBTTask_AvoidPlayer::GetStaticDescription() const
{
	return Super::GetStaticDescription();

	return FString::Printf(TEXT("Vector %s"), *BlackboardKey.SelectedKeyName.ToString());
}

UBTTask_AvoidPlayer::UBTTask_AvoidPlayer()
{
	NodeName = "Avoid Player";

	// Filter for only vectors.
	BlackboardKey.AddVectorFilter(this, GET_MEMBER_NAME_CHECKED(UBTTask_AvoidPlayer, BlackboardKey));
}
