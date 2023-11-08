// Fill out your copyright notice in the Description page of Project Settings.


#include "BaseAI/NoiseTrap/BaseAINoiseTrapController.h"

#include "BehaviorTree/BehaviorTree.h"
#include "BehaviorTree/BehaviorTreeComponent.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Perception/AIPerceptionComponent.h"
#include "Perception/AISenseConfig_Hearing.h"
#include "Perception/AISenseConfig_Sight.h"
#include "Perception/PerceptionCharacter.h"


ABaseAINoiseTrapController::ABaseAINoiseTrapController(FObjectInitializer const& ObjectInitializer)
{
	// Initialize Components BT && BB 
	BTComp = CreateDefaultSubobject<UBehaviorTreeComponent>(TEXT("BehaviorTreeComponent"));
	BBComp = CreateDefaultSubobject<UBlackboardComponent>(TEXT("BlackboardComponent"));
}

void ABaseAINoiseTrapController::BeginPlay()
{
	Super::BeginPlay();
	// If the behaviour tree is valid
	if (IsValid(BT.Get()))
	{
		// Run behaviour tree.
		RunBehaviorTree(BT.Get());

		// Then Run the BTComponent using the BT Asset.
		BTComp->StartTree(*BT.Get());
	};
}

void ABaseAINoiseTrapController::setupInit()
{
	// SubObject for Sight 
	Config_Sight = CreateDefaultSubobject<UAISenseConfig_Sight>("Sight Config");
	
	// Sight Config // 
	SetPerceptionComponent(*CreateDefaultSubobject<UAIPerceptionComponent>(TEXT("Perception Component")));
	
	if (Config_Sight)
	{
		Config_Sight->SightRadius = 200.f;
		//Config_Sight->LoseSightRadius = Config_Sight->SightRadius + 100.f;
		Config_Sight->PeripheralVisionAngleDegrees = 360.f;
		//Config_Sight->SetMaxAge(3.f);

		Config_Sight->DetectionByAffiliation.bDetectEnemies = true;
		Config_Sight->DetectionByAffiliation.bDetectFriendlies = true;
		Config_Sight->DetectionByAffiliation.bDetectNeutrals = true;
		
		// SubObject for Hearing
		Config_Hearing = CreateDefaultSubobject<UAISenseConfig_Hearing>("Hearing Config");

		if (Config_Hearing)
		{

			Config_Hearing->HearingRange = 900.f;
			Config_Hearing->SetMaxAge(2.f);
			Config_Hearing->DetectionByAffiliation.bDetectEnemies = true;
			Config_Hearing->DetectionByAffiliation.bDetectFriendlies = true;
			Config_Hearing->DetectionByAffiliation.bDetectNeutrals = true;
			GetPerceptionComponent()->ConfigureSense(*Config_Hearing);

			GetPerceptionComponent()->SetDominantSense(*Config_Hearing->GetSenseImplementation());
			// might need to be moved to tick 
			GetPerceptionComponent()->OnTargetPerceptionUpdated.AddDynamic(this, &ABaseAINoiseTrapController::OnTargetDetected);
			GetPerceptionComponent()->ConfigureSense(*Config_Sight);
		}
	}
}


void ABaseAINoiseTrapController::OnTargetDetected(AActor* Actor, FAIStimulus Stimulus)
{
	// (Delegate Call) When a pawn enters the sight of current AI, if it has stimulus it will decide on how to react.
	if(auto const Predator = Cast<APerceptionCharacter>(Actor))
	{
		if(Stimulus.Type == UAISense::GetSenseID<UAISenseConfig_Hearing>())
		{
			UE_LOG(LogTemp, Warning, TEXT("ALERT CAN HEAR PLAYER!") );
			// Tells Blackboard that we want to make a new boolean with the key name CanSeePrey, 
			GetBlackboardComponent()->SetValueAsBool("CanSeePredator", Stimulus.WasSuccessfullySensed());
			// OR, instead of a boolean we Assign a specific actor as a key (In this case a BBPrey).
			Blackboard->SetValueAsObject(BBHearPlayerKey, Actor);
		}
	} else if (auto const Player = Cast<APerceptionCharacter>(Actor))
	{
		if(Stimulus.Type == UAISense::GetSenseID<UAISenseConfig_Sight>()){
			UE_LOG(LogTemp, Warning, TEXT("ALERT CAN SEE PLAYER!!") );
			// Tells Blackboard that we want to make a new boolean with the key name CanSeePrey, 
			GetBlackboardComponent()->SetValueAsBool("CanSeePredator", Stimulus.WasSuccessfullySensed());
			// OR, instead of a boolean we Assign a specific actor as a key (In this case a BBPrey).
			Blackboard->SetValueAsObject(BBSeePlayerKey, Actor);
		}
	}
}

void ABaseAINoiseTrapController::OnPossess(APawn* InPawn)
{
	Super::OnPossess(InPawn);
	if(IsValid(BT.Get()))
	{
		// Check is BlackBoard comp is valid.
		if(IsValid(Blackboard.Get()))
		{
			// boolean that checks if blackboard is initilaized.
			// Get the blackboard asset for the Behaviour Tree. 
			Blackboard->InitializeBlackboard((*BT.Get()->BlackboardAsset));
		}
	}
}
