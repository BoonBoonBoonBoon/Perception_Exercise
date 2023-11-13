// Fill out your copyright notice in the Description page of Project Settings.


#include "BaseAI/ChaseAI/ChaseAiController.h"

#include "BaseAI/NoiseTrap/NoiseTrapAI.h"
#include "BaseAI/PreyAI/PreyAIPawn.h"
#include "BehaviorTree/BehaviorTree.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "DSP/Osc.h"
#include "Perception/AIPerceptionComponent.h"
#include "Perception/PerceptionCharacter.h"

AChaseAiController::AChaseAiController(FObjectInitializer const& ObjectInitializer)
{
	BBComp = CreateDefaultSubobject<UBlackboardComponent>("BlackBoard");	
	BTComp = CreateDefaultSubobject<UBehaviorTreeComponent>(TEXT("BTComp"));

	// Assigns the controller a team
	TeamId = FGenericTeamId(3);
	
	SetupInit();
}

void AChaseAiController::OnTargetDetected(AActor* Actor, FAIStimulus const Stimulus)
{
	// (Delegate Call) When a pawn enters the sight of current AI, if it has stimulus it will decide on how to react.
	/*if (auto const Player = Cast<APerceptionCharacter>(Actor)) // If Actor is Player Class
	{
		if(Stimulus.WasSuccessfullySensed())
		{
			//UE_LOG(LogTemp, Warning, TEXT("ChaseAI - Can Sense Player")); // Log that AI Senses player
			GetBlackboardComponent()->SetValueAsBool("SensedPlayer", Stimulus.WasSuccessfullySensed());
		}
		
		if (Stimulus.Type == UAISense::GetSenseID<UAISenseConfig_Hearing>()) // If the Stimulus Type was Noise
		{
			UE_LOG(LogTemp, Warning, TEXT("ChaseAI - Can Hear Player")); // Log that AI Hears player
			GetBlackboardComponent()->SetValueAsBool("HeardNoise", Stimulus.WasSuccessfullySensed()); // Set The boolean Value in BB to true if was sensed.
		}
			else if(Stimulus.Type == UAISense::GetSenseID<UAISenseConfig_Sight>()) // If the Stimulus type was sight
		{
				UE_LOG(LogTemp, Warning, TEXT("ChaseAI - Can See Player")); // Log that AI sees player
				GetBlackboardComponent()->SetValueAsBool("CanSeePlayer", Stimulus.WasSuccessfullySensed()); // Set The boolean Value in BB to true if was sensed.
		}
	}*/

	if(GetTeamAttitudeTowards(*Actor))
	{
		if(ETeamAttitude::Hostile)
		{
			if(Stimulus.WasSuccessfullySensed())
			{
				UE_LOG(LogTemp, Warning, TEXT("ChaseAI - Can Sense Player")); // Log that AI Senses player
				GetBlackboardComponent()->SetValueAsBool("SensedPlayer", Stimulus.WasSuccessfullySensed());
			}
		
			if (Stimulus.Type == UAISense::GetSenseID<UAISenseConfig_Hearing>()) // If the Stimulus Type was Noise
				{
				UE_LOG(LogTemp, Warning, TEXT("ChaseAI - Can Hear Player")); // Log that AI Hears player
				GetBlackboardComponent()->SetValueAsBool("HeardNoise", Stimulus.WasSuccessfullySensed()); // Set The boolean Value in BB to true if was sensed.
				}
			else if(Stimulus.Type == UAISense::GetSenseID<UAISenseConfig_Sight>()) // If the Stimulus type was sight
				{
				UE_LOG(LogTemp, Warning, TEXT("ChaseAI - Can See Player")); // Log that AI sees player
				GetBlackboardComponent()->SetValueAsBool("CanSeePlayer", Stimulus.WasSuccessfullySensed()); // Set The boolean Value in BB to true if was sensed.
				}
		}
	}

	
	//if(ActorHasTag()){}
	
	
	/*if(auto const Prey = Cast<APreyAIPawn>(Actor))
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
			OnHearNoise(Actor, Actor->GetActorLocation(), 1);
		}
	}*/
}

void AChaseAiController::OnHearNoise(AActor* ActorInstigator, const FVector& Location,float Volume)
{
	//if();
}

// See BTTask_MoveToNoise
bool AChaseAiController::ShouldReactToNoise(AActor* NoiseInstigator) const
{
	if (NoiseInstigator)
	{
		if(GetTeamAttitudeTowards(*NoiseInstigator))
		{
			if (ETeamAttitude::Neutral || ETeamAttitude::Hostile)
			{
				return true;
			}
		}
		/*// Might Have to change to Player I.E.
		//return NoiseInstigator != nullptr && NoiseInstigator->IsA<APlayerCharacter>();
		if (auto const Trap = Cast<ANoiseTrapAI>(NoiseInstigator))
		{
			return true;
		}
		else if (auto const Player = Cast<APerceptionCharacter>(NoiseInstigator))
		{
			return true;
		}*/
	}
	return false;
}

// See BTTask_MoveToSight
bool AChaseAiController::ShouldReactToSight(AActor* SightInstigator) const
{
	if (SightInstigator)
	{
		if (GetTeamAttitudeTowards(*SightInstigator))
		{
			if (ETeamAttitude::Neutral)
			{
				return false;
				
			} else if (ETeamAttitude::Hostile)
			{
				return true;
			}
		}

		/*if (auto const Trap = Cast<ANoiseTrapAI>(SightInstigator))
		{
			return false;
		}
		if (auto const trap = Cast<APerceptionCharacter>(SightInstigator))
		{
			return true;
		}*/
	}
	return false;
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
		SightConfig->SetMaxAge(2.0f);

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
			HearingConfig->SetMaxAge(1.0f);
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

		Blackboard->SetValueAsInt("WaypointIndex", 0);
		
		// Run behaviour tree.
		RunBehaviorTree(BT.Get());

		// Then Run the BTComponent using the BT Asset.
		BTComp->StartTree(*BT.Get());
	};
}

ETeamAttitude::Type AChaseAiController::GetTeamAttitudeTowards(const AActor& Other) const
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


