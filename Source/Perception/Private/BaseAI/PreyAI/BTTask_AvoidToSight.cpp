// Fill out your copyright notice in the Description page of Project Settings.


#include "BaseAI/PreyAI/BTTask_AvoidToSight.h"
#include "BaseAI/PreyAI/AIPreyController.h"
#include "Perception/AIPerceptionComponent.h"
#include "Perception/AISenseConfig_Sight.h"

UBTTask_AvoidToSight::UBTTask_AvoidToSight()
{
}

EBTNodeResult::Type UBTTask_AvoidToSight::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	// Get the AI controller and pawn
	AAIPreyController* Controller = Cast<AAIPreyController>(OwnerComp.GetAIOwner());

	if (Controller)
	{
		// Get the perception component to use 
		UAIPerceptionComponent* PerceptionComponent = Controller->GetAIPerceptionComponent();

		if (PerceptionComponent)
		{
			// Makes an array for AActor class 
			TArray<AActor*> PercivedActors;
			// The perception component gets all current actors that is has seen.
			PerceptionComponent->GetCurrentlyPerceivedActors(UAISenseConfig_Sight::StaticClass(), PercivedActors);

			// Loop through all the actors being seen 
			for (AActor* PercivedActor : PercivedActors)
			{
				// Retrieve information if the ai should react or not. (Team ID's)
				if (Controller->ShouldReactToSight(PercivedActor))
				{
					// Retrieve information about the perceived sight
					FVector SightLocation = PercivedActor->GetActorLocation();

					// Cast to the specific actor controller we want to move.
					AAIPreyController* PreyAi = Cast<AAIPreyController>(Controller->GetPawn());
					if (PreyAi)
					{
						// Calculate a location to run away from the detected actor
						FVector RunAwayLocation = CalulateAvoidanceLocation(PreyAi, PercivedActor);

						// Move the AI to the calculated location
						PreyAi->MoveToLocation(RunAwayLocation);

						// Optionally, adjust the AI's rotation to face away from the detected actor
						FRotator NewRotation = (RunAwayLocation - PreyAi->GetPawn()->GetActorLocation()).Rotation();
						PreyAi->GetPawn()->SetActorRotation(NewRotation);
						UE_LOG(LogTemp, Warning, TEXT("RunAwayLocation: %s"), *RunAwayLocation.ToString());
					}
					return EBTNodeResult::Succeeded;
				}
			}
		}
	}
	return EBTNodeResult::Failed;
}

FVector UBTTask_AvoidToSight::CalulateAvoidanceLocation(AAIController* AIController, AActor* DetecedActor)
{
	// Calculate a location opposite to the detected actor for the AI to run away
	FVector RunAwayDirection = AIController->GetPawn()->GetActorLocation() - DetecedActor->GetActorLocation();
	RunAwayDirection.Normalize();

	float RunAwayDistance = 500.0f; // Adjust as needed
	FVector RunAwayLocation = AIController->GetPawn()->GetActorLocation() + RunAwayDirection * RunAwayDistance;

	return RunAwayLocation;
}

