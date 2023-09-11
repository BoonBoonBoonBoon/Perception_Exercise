// Fill out your copyright notice in the Description page of Project Settings.


#include "BehaviorTree/BlackboardComponent.h"
#include "BehaviorTree/BehaviorTreeComponent.h"
#include "BehaviorTree/BehaviorTree.h"
#include "BaseAI/AvoidAI/PreyController.h"

#include "Perception/PerceptionCharacter.h"

void APreyController::OnPerceptionUpdated(TArray<AActor*> UpdatedActors)
{
	//if the actor exists inside the updatedActors array register him
	// : https://discuss.codecademy.com/t/the-meaning-of-colon-in-c/674663
	// moves through each actor like a normal loop
	for (AActor* Actor : UpdatedActors)
	{
		if (Actor->IsA<APerceptionCharacter>() && !GetSeeingPawn())
		{
			BlackboardComp->SetValueAsObject(BlackboardEnemyKey, Actor);
			return;
		}
	}
	//The character doesn't exist in our updated actors - so make sure
	//to delete any previous reference of him from the blackboard
	BlackboardComp->SetValueAsObject(BlackboardEnemyKey, nullptr);
}

APreyController::APreyController()
{
	//Components Init.
	BehaviorTreeComp = CreateDefaultSubobject<UBehaviorTreeComponent>(FName("BehaviorComp"));
 
	BlackboardComp = CreateDefaultSubobject<UBlackboardComponent>(FName("BlackboardComp"));
 
	AiPerceptionComponent = CreateDefaultSubobject<UAIPerceptionComponent>(FName("PerceptionComp"));
 
	//Create a Sight Sense
	Sight = CreateDefaultSubobject<UAISenseConfig_Sight>(FName("Sight Config"));
 
	Sight->SightRadius = 1000.f;
	Sight->LoseSightRadius = 1500.f;
	Sight->PeripheralVisionAngleDegrees = 130.f;
 
	//Tell the sight sense to detect everything
	Sight->DetectionByAffiliation.bDetectEnemies = true;
	Sight->DetectionByAffiliation.bDetectFriendlies = true;
	Sight->DetectionByAffiliation.bDetectNeutrals = true;
 
	//Register the sight sense to our Perception Component
	AiPerceptionComponent->ConfigureSense(*Sight);
}

void APreyController::OnPossess(APawn* InPawn)
{
	Super::OnPossess(InPawn);

	if (BehaviorTree)
	{
		//Initialize the Blackboard and start the attached behavior tree
		BlackboardComp->InitializeBlackboard(*BehaviorTree->BlackboardAsset);
		BehaviorTreeComp->StartTree(*BehaviorTree);
	}
 
	//Register the OnPerceptionUpdated function to fire whenever the AIPerception get's updated
	//AiPerceptionComponent->OnPerceptionUpdated(this, &APreyController::OnPerceptionUpdated)
	
}

AActor* APreyController::GetSeeingPawn()
{
	//Return the seeing pawn
	UObject* object = BlackboardComp->GetValueAsObject(BlackboardEnemyKey);
 
	return object ?  Cast<AActor>(object) : nullptr;
}

