// Fill out your copyright notice in the Description page of Project Settings.


#include "BaseAI/ChaseAI/BTTask_MoveToNoise.h"

#include "BaseAI/ChaseAI/ChaseAiController.h"
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
				if(Controller->ShouldReactToNoise)
			}
		}
	}
	
	return Super::ExecuteTask(OwnerComp, NodeMemory);
}
