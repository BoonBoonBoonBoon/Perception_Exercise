// Fill out your copyright notice in the Description page of Project Settings.


#include "BaseAI/PreyAI/AIPreyController.h"
#include "Perception/AISenseConfig_Sight.h"
#include "BaseAI/AIController_Base.h"
#include "BaseAI/ChaseAI/ChaseAI.h"
#include "BehaviorTree/BehaviorTree.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Perception/PerceptionCharacter.h"

AAIPreyController::AAIPreyController(FObjectInitializer const& ObjectInitializer)
{
	BTComp = CreateDefaultSubobject<UBehaviorTreeComponent>(TEXT("BehaviorTreeComponent"));
	BBComp = CreateDefaultSubobject<UBlackboardComponent>(TEXT("BlackboardComponent"));

	TeamId= FGenericTeamId(4);
	
	setupInit();
}

void AAIPreyController::BeginPlay()
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

void AAIPreyController::setupInit()
{
	Config_Hearing = CreateDefaultSubobject<UAISenseConfig_Hearing>("Hearing Config");
	Config_Sight = CreateDefaultSubobject<UAISenseConfig_Sight>("Sight Config");

	if(Config_Sight)
	{
		if(Config_Hearing)
		{
			// Sight Config
			SetPerceptionComponent(*CreateDefaultSubobject<UAIPerceptionComponent>(TEXT("Perception Component")));
			Config_Sight->SightRadius = 400.f;
			Config_Sight->LoseSightRadius = Config_Sight->SightRadius + 100.f;
			Config_Sight->PeripheralVisionAngleDegrees = 90.f;
			Config_Sight->SetMaxAge(3.f);
			
			Config_Sight->AutoSuccessRangeFromLastSeenLocation = 520.f;
			Config_Sight->DetectionByAffiliation.bDetectEnemies = true;
			Config_Sight->DetectionByAffiliation.bDetectFriendlies = true;
			Config_Sight->DetectionByAffiliation.bDetectNeutrals = true;

			// Hearing Config
			Config_Hearing->HearingRange = 900.f;
			Config_Hearing->SetMaxAge(2.f);
			Config_Hearing->DetectionByAffiliation.bDetectEnemies = true;
			Config_Hearing->DetectionByAffiliation.bDetectFriendlies = true;
			Config_Hearing->DetectionByAffiliation.bDetectNeutrals = true;
			GetPerceptionComponent()->ConfigureSense(*Config_Hearing);
			
			GetPerceptionComponent()->SetDominantSense(*Config_Hearing->GetSenseImplementation());
			// might need to be moved to tick 
			GetPerceptionComponent()->OnTargetPerceptionUpdated.AddDynamic(this, &AAIPreyController::OnTargetDetected);
			GetPerceptionComponent()->ConfigureSense(*Config_Sight);
			
		}
	}
}

void AAIPreyController::OnTargetDetected(AActor* Actor, FAIStimulus Stimulus)
{
	// (Delegate Call) When a pawn enters the sight of current AI, if it has stimulus it will decide on how to react.
	/*if(auto const Predator = Cast<AChaseAI>(Actor))
	{
		UE_LOG(LogTemp, Warning, TEXT("Predator!") );
		// Tells Blackboard that we want to make a new boolean with the key name CanSeePrey, 
		GetBlackboardComponent()->SetValueAsBool("CanSeePredator", Stimulus.WasSuccessfullySensed());
		// OR, instead of a boolean we Assign a specific actor as a key (In this case a BBPrey).
		Blackboard->SetValueAsObject(BBPredatorKey, Actor);
		
	} else if (auto const Player = Cast<APerceptionCharacter>(Actor))
	{
		UE_LOG(LogTemp, Warning, TEXT("Predator!") );
		// Tells Blackboard that we want to make a new boolean with the key name CanSeePrey, 
		GetBlackboardComponent()->SetValueAsBool("CanSeePredator", Stimulus.WasSuccessfullySensed());
		// OR, instead of a boolean we Assign a specific actor as a key (In this case a BBPrey).
		Blackboard->SetValueAsObject(BBPredatorKey, Actor);
	}*/

	if (GetTeamAttitudeTowards(*Actor))
	{
		if constexpr (ETeamAttitude::Hostile)
		{
			if (Stimulus.WasSuccessfullySensed())
			{
				UE_LOG(LogTemp, Warning, TEXT("PreyAI - Can Sense Something")); // Log that AI Senses player
				//GetBlackboardComponent()->SetValueAsBool("SensedPlayer", Stimulus.WasSuccessfullySensed());
			}

			if (Stimulus.Type == UAISense::GetSenseID<UAISenseConfig_Hearing>()) // If the Stimulus Type was Noise
			{
				UE_LOG(LogTemp, Warning, TEXT("PreyAI - Can Hear Something")); // Log that AI Hears player
				GetBlackboardComponent()->SetValueAsBool("HearPredator", Stimulus.WasSuccessfullySensed());
				// Set The boolean Value in BB to true if was sensed.
			}
			 if (Stimulus.Type == UAISense::GetSenseID<UAISenseConfig_Sight>()) // If the Stimulus type was sight
			{
				UE_LOG(LogTemp, Warning, TEXT("PreyAI - Can See Something")); // Log that AI sees player
				GetBlackboardComponent()->SetValueAsBool("SeePredator", Stimulus.WasSuccessfullySensed());
				// Set The boolean Value in BB to true if was sensed.
			}
		}
	}
}

void AAIPreyController::OnPossess(APawn* InPawn)
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

ETeamAttitude::Type AAIPreyController::GetTeamAttitudeTowards(const AActor& Other) const
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
	if(igtaiActorBot == nullptr && igtaiActorPlayer == nullptr) // if Bot is 225
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
		
	} else if(fgtiThisBotTeamId == 2) // NoiseTrap Team 
	{
		// Noise Trap makes sound ???
		return ETeamAttitude::Neutral;
		
	} else // they are on different teams
	{
		return ETeamAttitude::Hostile;
	}
	
}

bool AAIPreyController::ShouldReactToNoise(AActor* NoiseInstigator) const
{
	return false;
}

bool AAIPreyController::ShouldReactToSight(AActor* SightInstigator) const
{
	if (SightInstigator)
	{
		if (GetTeamAttitudeTowards(*SightInstigator))
		{
			if (ETeamAttitude::Hostile)
			{
				return true;
			}
		}
		else if (GetTeamAttitudeTowards(*SightInstigator))
		{
			if (ETeamAttitude::Neutral)
			{
				return false;
			}
		}
	}
	return false;
}

