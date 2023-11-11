// Fill out your copyright notice in the Description page of Project Settings.


#include "BaseAI/ChaseAI/BTTask_MoveToNoise.h"

#include "NavigationSystem.h"
#include "BaseAI/ChaseAI/ChaseAI.h"
#include "BaseAI/ChaseAI/ChaseAiController.h"
#include "Blueprint/AIBlueprintHelperLibrary.h"
#include "Perception/AIPerceptionComponent.h"

UBTTask_MoveToNoise::UBTTask_MoveToNoise()
{
	NodeName = "MoveToNoise";
}

EBTNodeResult::Type UBTTask_MoveToNoise::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	// Gets Pawn
	AChaseAiController* Controller = Cast<AChaseAiController>(OwnerComp.GetAIOwner());
	if (Controller)
	{
		// Gets the perception component of the Controller
		UAIPerceptionComponent* PerceptionComponent = Controller->GetAIPerceptionComponent();
		if (PerceptionComponent)
		{
			// Array of AActor
			TArray<AActor*> PercivedActors;
			// The perception component gets all current actors that is has heard.
			PerceptionComponent->GetCurrentlyPerceivedActors(UAISenseConfig_Hearing::StaticClass(), PercivedActors);

			// Loops through all the actors that the ai has Heard 
			for (AActor* PercivedActor : PercivedActors)
			{
				//  may want to implement different logic here to determine which noise to react to
				if(Controller->ShouldReactToNoise(PercivedActor))
				{
					// Retrieve information about the perceived noise
					FVector NoiseLocation = PercivedActor->GetActorLocation();
					
					/*
					FVector NoiseLocation;
					float NoiseVolume;
					// doesnt Work
					//PerceptionComponent->GetNoiseInfo(PerceivedActor, NoiseLocation, NoiseVolume);
					*/

					AChaseAI* ChaseAi = Cast<AChaseAI>(Controller->GetPawn());
					if(ChaseAi)
					{
						// Move the AI to the noise location using SimpleMoveToLocation
						UAIBlueprintHelperLibrary::SimpleMoveToLocation(Controller, NoiseLocation);
					}
					return EBTNodeResult::Succeeded;
				}
			}
		}
	}
	return EBTNodeResult::Failed;
	
}
