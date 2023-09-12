// Fill out your copyright notice in the Description page of Project Settings.


#include "BehaviorTree/BlackboardComponent.h"
#include "BehaviorTree/BehaviorTreeComponent.h"
#include "BehaviorTree/BehaviorTree.h"
#include "BaseAI/AvoidAI/PreyController.h"

#include "Perception/PerceptionCharacter.h"

APreyController::APreyController(FObjectInitializer const& ObjectInitializer)
{
	// Adds the components to the ai controller
	BehaviorTreeComponent = CreateDefaultSubobject<UBehaviorTreeComponent>(TEXT("BehaviorTreeComponent"));
	BlackboardComponent = CreateDefaultSubobject<UBlackboardComponent>(TEXT("BlackboardComponent"));
	
	SetupPerception();
}

void APreyController::SetupPerception()
{
	// init 
	SightConfig = CreateDefaultSubobject<UAISenseConfig_Sight>(TEXT("Sight Config"));
	
	if (SightConfig)
	{
		SetPerceptionComponent(*CreateDefaultSubobject<UAIPerceptionComponent>(TEXT("Perception Component")));
		SightConfig->SightRadius = 400.f;
		SightConfig->LoseSightRadius = SightConfig->SightRadius + 25.f;
		SightConfig->PeripheralVisionAngleDegrees = 120.f;
		SightConfig->SetMaxAge(3.f);

		// Allows Ai to continue to see stimulis source if it remains within specified distance from last seen location 
		SightConfig->AutoSuccessRangeFromLastSeenLocation = 520.f;
		SightConfig->DetectionByAffiliation.bDetectEnemies = true;
		SightConfig->DetectionByAffiliation.bDetectFriendlies = true;
		SightConfig->DetectionByAffiliation.bDetectNeutrals = true;

		// Sets the dominant sense ( The main sense)
		GetPerceptionComponent()->SetDominantSense(*SightConfig->GetSenseImplementation());
		GetPerceptionComponent()->OnTargetPerceptionUpdated.AddDynamic(this, &APreyController::OnTargetDetected);
		GetPerceptionComponent()->ConfigureSense(*SightConfig);
	}
}

void APreyController::OnTargetDetected(AActor* Actor, FAIStimulus const Stimulus)
{
	if(auto* const ch = Cast<APerceptionCharacter>(Actor) )
	{
			GetBlackboardComponent()->SetValueAsBool("CanSeePlayer", Stimulus.WasSuccessfullySensed());
	}
}

void APreyController::BeginPlay()
{
	Super::BeginPlay();

	// Need to make sure the behavior tree runs, check if its valid.
	if(IsValid(BehaviorTree.Get()))
	{
		// Runs the Behavior tree
		RunBehaviorTree(BehaviorTree.Get());
		// Executes from root
		BehaviorTreeComponent->StartTree(*BehaviorTree.Get());
	}
	
}

void APreyController::OnPossess(APawn* InPawn)
{
	Super::OnPossess(InPawn);

	// Need to initalize the BT and BB
	// .Get is a explicit conversion.
	if(IsValid(Blackboard.Get()) && IsValid(BehaviorTree.Get()))
	{
		
		Blackboard->InitializeBlackboard((*BehaviorTree.Get()->BlackboardAsset));
	}
	
}

AActor* APreyController::GetSeeingPawn()
{
}


