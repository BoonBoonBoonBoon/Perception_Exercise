// Fill out your copyright notice in the Description page of Project Settings.


#include "BaseAI/AIController_Base.h"
#include "BehaviorTree/BehaviorTree.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Perception\Public\BaseAI\AIBase.h"

AAIController_Base::AAIController_Base(FObjectInitializer const& ObjectInitializer)
{
	// Adds the components to the ai controller
	BehaviorTreeComponent = CreateDefaultSubobject<UBehaviorTreeComponent>(TEXT("BehaviorTreeComponent"));
	BlackboardComponent = CreateDefaultSubobject<UBlackboardComponent>(TEXT("BlackboardComponent"));

	Perception = CreateDefaultSubobject<UAIBase_PawnSensingComponent>(TEXT("Sensing"));
}

void AAIController_Base::BeginPlay()
{
	Super::BeginPlay();
	// Check if the behavior tree is valid
	if(IsValid(BehaviorTree.Get()))
	{
		// Runs the Behavior tree
		RunBehaviorTree(BehaviorTree.Get());
		// Executes from root
		BehaviorTreeComponent->StartTree(*BehaviorTree.Get());
	}
	
}

// if the Pawn is the NPC and the cast succeeds 
void AAIController_Base::OnPossess(APawn* InPawn)
{
	Super::OnPossess(InPawn);

	// .Get is a explicit conversion.
	if(IsValid(Blackboard.Get())&& IsValid(BehaviorTree.Get()))
	{
		Blackboard->InitializeBlackboard((*BehaviorTree.Get()->BlackboardAsset));
	}
	
}
