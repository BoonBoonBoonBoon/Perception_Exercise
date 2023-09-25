// Fill out your copyright notice in the Description page of Project Settings.


#include "BaseAI/ChaseAI/ChaseAiController.h"

#include "BaseAI/AvoidAI/AIPrey.h"
#include "BehaviorTree/BehaviorTree.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Perception/AIPerceptionComponent.h"
#include "Perception/PerceptionCharacter.h"

AChaseAiController::AChaseAiController(FObjectInitializer const& ObjectInitializer)
{
	BBComp = CreateDefaultSubobject<UBlackboardComponent>("BlackBoard");	
	BTComp = CreateDefaultSubobject<UBehaviorTreeComponent>(TEXT("BTComp"));
	
	SetupInit();
}

void AChaseAiController::OnTargetDetected(AActor* Actor, FAIStimulus const Stimulus)
{
	// (Delegate Call) When a pawn enters the sight of current AI, if it has stimulus it will decide on how to react.
	if(auto const Prey = Cast<AAIPrey>(Actor))
	{
		UE_LOG(LogTemp, Warning, TEXT("Prey!") );
		// Tells Blackboard that we want to make a new boolean with the key name CanSeePrey, 
		GetBlackboardComponent()->SetValueAsBool("CanSeePrey", Stimulus.WasSuccessfullySensed());
		// OR, instead of a boolean we Assign a specific actor as a key (In this case a BBPrey).
		Blackboard->SetValueAsObject(BBPreyKey, Actor);
		
	} else if (auto const Player = Cast<APerceptionCharacter>(Actor))
	{
		UE_LOG(LogTemp, Warning, TEXT("Player!") );
		GetBlackboardComponent()->SetValueAsBool("CanSeePlayer", Stimulus.WasSuccessfullySensed());
		Blackboard->SetValueAsObject(BBEnemyKey, Actor);
		if(HearingConfig)
		{
			
		}
	}
}

void AChaseAiController::OnHearNoise(APawn* PawnInstigator, const FVector& Location,float Volume)
{
}


void AChaseAiController::OnPossess(APawn* InPawn)
{
	Super::OnPossess(InPawn);

	// Need to initialize the BT & BB.
	// Check if Behaviour Tree is valid.
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


void AChaseAiController::SetupInit()
{

	// Sight Config Etc.
	SightConfig=CreateDefaultSubobject<UAISenseConfig_Sight>(TEXT("SightConfig"));
	if(SightConfig)
	{
		
		// Perception Init.
		SetPerceptionComponent(*CreateDefaultSubobject<UAIPerceptionComponent>(TEXT("Perception Component")));
		SightConfig->SightRadius = 600.f;
		SightConfig->LoseSightRadius = SightConfig->SightRadius + 50.f;
		SightConfig->PeripheralVisionAngleDegrees = 45.f;
		SightConfig->SetMaxAge(5.f);

		// Sets AI to continue seeing pawn detected location if it still remains within a local area.
		SightConfig->AutoSuccessRangeFromLastSeenLocation = 800.f;
		SightConfig->DetectionByAffiliation.bDetectEnemies = true;
		SightConfig->DetectionByAffiliation.bDetectFriendlies = true;
		SightConfig->DetectionByAffiliation.bDetectNeutrals = true;
		// Hearing Config Etc.
		HearingConfig=CreateDefaultSubobject<UAISenseConfig_Hearing>(TEXT("HearingConfig"));
		if(HearingConfig)
		{

			HearingConfig->HearingRange = 900.f;
			HearingConfig->DetectionByAffiliation.bDetectEnemies = true;
			HearingConfig->DetectionByAffiliation.bDetectFriendlies = true;
			HearingConfig->DetectionByAffiliation.bDetectNeutrals = true;
			GetPerceptionComponent()->ConfigureSense(*HearingConfig);
		}

		// Sets Dominant sense (Main) GetSense returns the current implementation.
		GetPerceptionComponent()->SetDominantSense(*HearingConfig->GetSenseImplementation());
		// Delegate to sense function, when perception receives new info fire off target detection function. 
		GetPerceptionComponent()->OnTargetPerceptionUpdated.AddDynamic(this, &AChaseAiController::OnTargetDetected);
		// Makes everything above configured and set to the new config.
		GetPerceptionComponent()->ConfigureSense(*SightConfig);
		
		
	}
}

void AChaseAiController::BeginPlay()
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