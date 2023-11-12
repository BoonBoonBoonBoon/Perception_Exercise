// Fill out your copyright notice in the Description page of Project Settings.


#include "BaseAI/ChaseAI/BTTask_MoveToSight.h"

#include "BaseAI/ChaseAI/ChaseAI.h"
#include "BaseAI/ChaseAI/ChaseAiController.h"
#include "Blueprint/AIBlueprintHelperLibrary.h"
#include "Perception/AIPerceptionComponent.h"

UBTTask_MoveToSight::UBTTask_MoveToSight()
{
	NodeName = "SightMoveToTask";
}

EBTNodeResult::Type UBTTask_MoveToSight::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	// Get the AI controller and pawn
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
			PerceptionComponent->GetCurrentlyPerceivedActors(UAISenseConfig_Sight::StaticClass(), PercivedActors);

			for (AActor* PercivedActor : PercivedActors)
			{
				//  may want to implement different logic here to determine which noise to react to
				if (Controller->ShouldReactToSight(PercivedActor))
				{
					// Retrieve information about the perceived noise
					FVector SightLocation = PercivedActor->GetActorLocation();

					AChaseAI* ChaseAi = Cast<AChaseAI>(Controller->GetPawn());
					if (ChaseAi)
					{
						// Move the AI to the noise location using SimpleMoveToLocation
						UAIBlueprintHelperLibrary::SimpleMoveToLocation(Controller, SightLocation);
					}
					return EBTNodeResult::Succeeded;
				}
			}
		}
	}
	return EBTNodeResult::Failed;
}
