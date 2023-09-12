// Fill out your copyright notice in the Description page of Project Settings.


#include "BaseAI/AIController_Base.h"
#include "BehaviorTree/BehaviorTree.h"
#include "Perception/AIPerceptionComponent.h"
#include "Perception/AISenseConfig_Sight.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Perception/PerceptionCharacter.h"
#include "Perception\Public\BaseAI\AIBase.h"

AAIController_Base::AAIController_Base(FObjectInitializer const& ObjectInitializer)
{
	// Adds the components to the ai controller
	BehaviorTreeComponent = CreateDefaultSubobject<UBehaviorTreeComponent>(TEXT("BehaviorTreeComponent"));
	BlackboardComponent = CreateDefaultSubobject<UBlackboardComponent>(TEXT("BlackboardComponent"));

	//Perception = CreateDefaultSubobject<UBasicPerceptionComponent>(TEXT("Perception"));

	SetupPerceptionSystem();
}



void AAIController_Base::SetupPerceptionSystem()
{
	
	SightConfig = CreateDefaultSubobject<UAISenseConfig_Sight>(TEXT("Sight Config"));
	/*void(UAIPerceptionComponent::* ConfigureSense)(UAISenseConfig&) = UBasicPerceptionComponent::ConfigureSense;
	ConfigureSense(*SightConfig);*/
	
	//HearingConfig = CreateDefaultSubobject<UAISenseConfig_Hearing>(TEXT("Hearing Perception"));
	//ConfigureSense(*HearingConfig);
	
	if (SightConfig)
	{
		SetPerceptionComponent(*CreateDefaultSubobject<UAIPerceptionComponent>(TEXT("Perception Component")));
		SightConfig->SightRadius = 400.f;
		SightConfig->LoseSightRadius = SightConfig->SightRadius + 25.f;
		SightConfig->PeripheralVisionAngleDegrees = 90.f;
		SightConfig->SetMaxAge(5.f);

		// Allows Ai to continue to see stimulis source if it remains within specified distance from last seen location 
		SightConfig->AutoSuccessRangeFromLastSeenLocation = 520.f;
		SightConfig->DetectionByAffiliation.bDetectEnemies = true;
		SightConfig->DetectionByAffiliation.bDetectFriendlies = true;
		SightConfig->DetectionByAffiliation.bDetectNeutrals = true;

		// Sets the dominant sense ( The main sense)
		GetPerceptionComponent()->SetDominantSense(*SightConfig->GetSenseImplementation());

		// might need to be moved to tick 
		GetPerceptionComponent()->OnTargetPerceptionUpdated.AddDynamic(this, &AAIController_Base::OnTargetDetected);
		GetPerceptionComponent()->ConfigureSense(*SightConfig);
	}
}


void AAIController_Base::OnTargetDetected(AActor* Actor, FAIStimulus const Stimulus)
{

	if(auto* const ch = Cast<APerceptionCharacter>(Actor))
	{
		GetBlackboardComponent()->SetValueAsBool("CanSeePlayer", Stimulus.WasSuccessfullySensed());
	}

	
}

/*void AAIController_Base::OnPerceptionUpdated(TArray<AActor*> UpdatedActors)
{
	//if the actor exists inside the updatedActors array register him
	// : https://discuss.codecademy.com/t/the-meaning-of-colon-in-c/674663
	// moves through each actor like a normal loop 
	for (AActor* Actor : UpdatedActors)
	{
		if(Actor->IsA<APerceptionCharacter>() && !GetSeeingPawn())
		{
			BlackboardComponent->SetValueAsObject(BlackboardEnemyKey, Actor);
			return;
		}
	}
	// The Character doesnt exist in the updated actors make it so
	BlackboardComponent->SetValueAsObject(BlackboardEnemyKey, nullptr)
}*/

/*AActor* AAIController_Base::GetSeeingPawn()
{
}*/

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

