// Fill out your copyright notice in the Description page of Project Settings.


#include "BaseAI/NoiseTrap/NoiseTrapController.h"

#include "BaseAI/NoiseTrap/NoiseTrapAI.h"
#include "BehaviorTree/BehaviorTree.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Perception/AIPerceptionComponent.h"
#include "Perception/PerceptionCharacter.h"

ANoiseTrapController::ANoiseTrapController(FObjectInitializer const& ObjectInitializer)
{
	// Initialize Components BT && BB 
	BTComp = CreateDefaultSubobject<UBehaviorTreeComponent>(TEXT("BehaviorTreeComponent"));
	BBComp = CreateDefaultSubobject<UBlackboardComponent>(TEXT("BlackboardComponent"));

	// Assigns the controller a team
	TeamId = FGenericTeamId(2);
	
	setupInit();
}

void ANoiseTrapController::BeginPlay()
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

void ANoiseTrapController::setupInit()
{
	// SubObject for Sight 
	Config_Sight = CreateDefaultSubobject<UAISenseConfig_Sight>("Sight Config");

	// Sight Config // 
	SetPerceptionComponent(*CreateDefaultSubobject<UAIPerceptionComponent>(TEXT("Perception Component")));
	if (Config_Sight)
	{
		Config_Sight->SightRadius = 500.f;
		Config_Sight->LoseSightRadius = Config_Sight->SightRadius + 200.f;
		Config_Sight->PeripheralVisionAngleDegrees = 180.f;
		Config_Sight->SetMaxAge(0.f);

		Config_Sight->DetectionByAffiliation.bDetectEnemies = true;
		Config_Sight->DetectionByAffiliation.bDetectFriendlies = true;
		Config_Sight->DetectionByAffiliation.bDetectNeutrals = true;

		// SubObject for Hearing
		Config_Hearing = CreateDefaultSubobject<UAISenseConfig_Hearing>("Hearing Config");

		if (Config_Hearing)
		{
			Config_Hearing->HearingRange = 800.f;
			Config_Hearing->SetMaxAge(0.f);
			Config_Hearing->DetectionByAffiliation.bDetectEnemies = true;
			Config_Hearing->DetectionByAffiliation.bDetectFriendlies = true;
			Config_Hearing->DetectionByAffiliation.bDetectNeutrals = true;
			GetPerceptionComponent()->ConfigureSense(*Config_Hearing);

			GetPerceptionComponent()->SetDominantSense(*Config_Hearing->GetSenseImplementation());
			// might need to be moved to tick 
			GetPerceptionComponent()->OnTargetPerceptionUpdated.AddDynamic(this, &ANoiseTrapController::OnTargetDetected);
			GetPerceptionComponent()->ConfigureSense(*Config_Sight);
		}
	}
}

void ANoiseTrapController::OnTargetDetected(AActor* Actor, FAIStimulus Stimulus)
{
	// (Delegate Call) When a pawn enters the sight of current AI, if it has stimulus it will decide on how to react.
	if (auto const Player = Cast<APerceptionCharacter>(Actor))
	{
		if (Stimulus.Type == UAISense::GetSenseID<UAISenseConfig_Hearing>())
		{
			UE_LOG(LogTemp, Warning, TEXT("ALERT CAN HEAR PLAYER!"));

			// Tells Blackboard that we want to make a new boolean with the key name CanSeePrey, 
			GetBlackboardComponent()->SetValueAsBool("CanSeePredator", Stimulus.WasSuccessfullySensed());

			// OR, instead of a boolean we Assign a specific actor as a key (In this case a BBPrey).
			Blackboard->SetValueAsObject(BBHearPlayerKey, Actor);
		}
		else if (Stimulus.Type == UAISense::GetSenseID<UAISenseConfig_Sight>())
		{
			UE_LOG(LogTemp, Warning, TEXT("TeamId of Agent: %d"), TeamId.GetId());

			
			UE_LOG(LogTemp, Warning, TEXT("ALERT CAN SEE PLAYER!!"))
			
			GetBlackboardComponent()->SetValueAsBool("CanSeePredator", Stimulus.WasSuccessfullySensed());

			Blackboard->SetValueAsObject(BBSeePlayerKey, Actor);
		}
	}
}

void ANoiseTrapController::OnPossess(APawn* InPawn)
{
	Super::OnPossess(InPawn);
	if (IsValid(BT.Get()))
	{
		// Check is BlackBoard comp is valid.
		if (IsValid(Blackboard.Get()))
		{
			// boolean that checks if blackboard is initilaized.
			// Get the blackboard asset for the Behaviour Tree. 
			Blackboard->InitializeBlackboard((*BT.Get()->BlackboardAsset));
		}
	}
}

ETeamAttitude::Type ANoiseTrapController::GetTeamAttitudeTowards(const AActor& Other) const
{

	// Checks if the actor is a pawn
	auto OtherPawn = Cast<APawn>(&Other);
	if(OtherPawn == nullptr)
	{
		return ETeamAttitude::Neutral;
	}

	// Check if Actor (Bot or Player) implements IGenericTeamAgentInterface.
	auto igtaiActorBot = Cast<IGenericTeamAgentInterface>(OtherPawn->GetController());
	auto igtaiActorPlayer = Cast<IGenericTeamAgentInterface>(&Other);
	if(igtaiActorBot == nullptr && igtaiActorPlayer == nullptr)
	{
		return ETeamAttitude::Neutral;
	}

	// Gets the TeamID of the Actor (Bot or Player)
	FGenericTeamId fgtiOtherActorTeamId = NULL;
	if(igtaiActorBot != nullptr)
	{
		fgtiOtherActorTeamId = igtaiActorBot->GetGenericTeamId();
	} else if (igtaiActorPlayer != nullptr)
	{
		fgtiOtherActorTeamId = igtaiActorPlayer->GetGenericTeamId();
	}

	// Determines ThisBot attitude towards the OtherActor (Bot or Player) as either Neutral, Friendly, or Hostile.
	FGenericTeamId fgtiThisBotTeamId = this->GetGenericTeamId();
	
	return Super::GetTeamAttitudeTowards(Other);
}




// Gets Pawn class 
/*ANoiseTrapAI* CheckSelf = Cast<ANoiseTrapAI>(GetPawn());
if (CheckSelf)
{
	// Assigns Pawn class to agent
	Agent = CheckSelf;
	// Log a warning message with ID
	FString DebugMessage = FString::Printf(TEXT("CheckSelfTRUE. ID: %d"), Agent->ID);
	GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Yellow, DebugMessage);
	// Log a warning message with ID
	UE_LOG(LogTemp, Warning, TEXT("CheckSelfTRUE. ID: %d"), Agent->ID);
		
	// Assigns the ID to Teamid to be used as an identifier
	TeamId = FGenericTeamId(Agent->ID);
}*/


/*
ETeamAttitude::Type ANoiseTrapController::GetTeamAttitudeTowards(const AActor& Other) const
{
	//return Super::GetTeamAttitudeTowards(Other);
	//UE_LOG(LogTemp, Warning, TEXT("TeamId of Other Actor: %d"), OtherActorTeamId.GetId());


	// check if Actor is a pawn
	const APawn* OtherPawn = Cast<APawn>(&Other);
	if (OtherPawn == nullptr)
	{
		return ETeamAttitude::Neutral;
	}

	// Check if Actor implements GenericTeamAgentInterface (If its a bot or player)
	auto PlayerIT = Cast<IGenericTeamAgentInterface>(&Other);
	class IGenericTeamAgentInterface* BotIT = Cast<IGenericTeamAgentInterface>(OtherPawn->GetController());
	if (BotIT == nullptr && PlayerIT == nullptr)
	{
		return ETeamAttitude::Neutral;
	}

	return {};
}
*/
