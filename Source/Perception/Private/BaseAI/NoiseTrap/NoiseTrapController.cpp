// Fill out your copyright notice in the Description page of Project Settings.


#include "BaseAI/NoiseTrap/NoiseTrapController.h"

#include "BaseAI/NoiseTrap/NoiseTrapAI.h"
#include "Perception/AIPerceptionListenerInterface.h"
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

	// Give the Actor a Tag to identify it
	Tags.Add(TEXT("NoiseTrap"));
	setupInit();

	SenseCall = 8;
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

void ANoiseTrapController::TimeToSense()
{
	if(!bCanMakeNoise)
	{
		// Decrements till 0
		SenseCall--;
		// Print the current countdown
		UE_LOG(LogTemp, Warning, TEXT("Countdown: %d"), SenseCall);

		if(SenseCall <= 0)
		{
			// Your action when the countdown reaches zero
			UE_LOG(LogTemp, Warning, TEXT("Timer Cleared!"))

			// Reset the countdown to 5 seconds for the next iteration
			SenseCall = 8;
			bCanMakeNoise = true;
			GetWorldTimerManager().ClearTimer(TimeToSenseHandle);
		}
	}
	return;
}

void ANoiseTrapController::OnTargetDetected(AActor* Actor, FAIStimulus Stimulus)
{
	// (Delegate Call) When a pawn enters the sight of current AI, if it has stimulus it will decide on how to react.
	if (auto const Player = Cast<APerceptionCharacter>(Actor))
	{
		if (Stimulus.Type == UAISense::GetSenseID<UAISenseConfig_Hearing>())
		{
			// Tells Blackboard that we want to make a new boolean with the key name CanSeePrey, 
			GetBlackboardComponent()->SetValueAsBool("CanSeePredator", Stimulus.WasSuccessfullySensed());
			// OR, instead of a boolean we Assign a specific actor as a key (In this case a BBPrey).
			Blackboard->SetValueAsObject(BBHearPlayerKey, Actor);

			// FirstTime Making Noise
			if (bFirstNoise)
			{
				Actor->MakeNoise(3.f, Agent, Actor->GetActorLocation());
				UE_LOG(LogTemp, Warning, TEXT("MakeNoise called for the first time, with (Hearing) loudness 3.0f at location %s"), *Actor->GetActorLocation().ToString());
				bFirstNoise = false;
				bCanMakeNoise = true;
			} else if(bCanMakeNoise && !bFirstNoise)
			{
				bCanMakeNoise = false;
				Actor->MakeNoise(3.f, Agent, Actor->GetActorLocation());
				UE_LOG(LogTemp, Warning, TEXT("MakeNoise called for the Second time, with (Hearing) loudness 3.0f at location %s"), *Actor->GetActorLocation().ToString());
				GetWorldTimerManager().SetTimer(TimeToSenseHandle, this, &ANoiseTrapController::TimeToSense, 1.f, true);
			}
		}
		/*else if (Stimulus.Type == UAISense::GetSenseID<UAISenseConfig_Sight>())
		{
			GetBlackboardComponent()->SetValueAsBool("CanSeePredator", Stimulus.WasSuccessfullySensed());
			Blackboard->SetValueAsObject(BBSeePlayerKey, Actor);

			// First Time Making Noise
			if (bFirstNoise)
			{
				Actor->MakeNoise(3.f, Agent, Actor->GetActorLocation());
				bFirstNoise = false;
			}
		}*/
	}
}

//UE_LOG(LogTemp, Warning, TEXT("TeamId of Agent: %d"), TeamId.GetId());
//UE_LOG(LogTemp, Warning, TEXT("ALERT! - NOISETRAP CAN SEE PLAYER!!"))
//Agent->MakeNoise(3.f, Agent, Agent->GetActorLocation());
// Log a message indicating that MakeNoise has been called
//UE_LOG(LogTemp, Warning, TEXT("MakeNoise called with (Sight) loudness 3.0f at location %s"),
// *Actor->GetActorLocation().ToString());

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

	// For Testing, Print ActorBot TeamID.
	/*
	if(igtaiActorBot != nullptr)
	{
		FGenericTeamId fgtiActorBotTeamId = igtaiActorBot->GetGenericTeamId();
		int iActorBotTeamId = (int)fgtiActorBotTeamId;
		FString fstrActorBotTeamId = FString::FromInt(iActorBotTeamId);
		GEngine->AddOnScreenDebugMessage(-1,15.0f, FColor::Yellow, fstrActorBotTeamId);
		UE_LOG(LogTemp, Warning, TEXT("%s"), *fstrActorBotTeamId);
	}
	// For Testing, Print ActorPlayer TeamID
	if(igtaiActorPlayer != nullptr)
	{
		FGenericTeamId fgtiActorPlayerTeamId = igtaiActorPlayer->GetGenericTeamId();
		int iActorPlayerTeamId = (int)fgtiActorPlayerTeamId;
		FString fstrActorPlayerTeamid = FString::FromInt(iActorPlayerTeamId);
		GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Green, fstrActorPlayerTeamid);
		UE_LOG(LogTemp, Warning, TEXT("%s"), *fstrActorPlayerTeamid);
	}
	*/
	
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
	if(fgtiThisBotTeamId == 225) // They are not on a team;
	{
		return ETeamAttitude::Neutral;
	} else if (fgtiThisBotTeamId == fgtiOtherActorTeamId) // They are on the same team
	{
		return ETeamAttitude::Friendly;
	} else // they are on different teams
	{
		return ETeamAttitude::Hostile;
	}
	

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
