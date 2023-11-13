// Fill out your copyright notice in the Description page of Project Settings.


#include "BaseAI/ChaseAI/ChaseAI.h"

#include "BaseAI/ChaseAI/ChaseAiController.h"
#include "BaseAI/Waypoints/WayPoints.h"
#include "Components/PawnNoiseEmitterComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Perception/AIPerceptionStimuliSourceComponent.h"
#include "Perception/AISense_Hearing.h"
#include "Perception/AISense_Sight.h"

// Sets default values
AChaseAI::AChaseAI()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	
	NoiseEmitter = CreateDefaultSubobject<UPawnNoiseEmitterComponent>(TEXT("PawnNoiseEmitter"));
}

void AChaseAI::OnOverlapBegin(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	
}

void AChaseAI::OnOverlapEnd(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
}

void AChaseAI::SetupStimulusSource()
{
	StimuliSourcePredator = CreateDefaultSubobject<UAIPerceptionStimuliSourceComponent>(TEXT("Stimulus Source"));
	if(StimuliSourcePredator)
	{
		StimuliSourcePredator->RegisterForSense(TSubclassOf<UAISense_Sight>());
		StimuliSourcePredator->RegisterForSense(TSubclassOf<UAISense_Hearing>());
		StimuliSourcePredator->RegisterWithPerceptionSystem();
	}
	
}

void AChaseAI::ReportNoise(USoundBase* SoundToPlay, float Volume)
{

	if(this->GetCharacterMovement()->speed >= 10.f)
	{
		
	}


	
	/*if(this->GetCharacterMovement()->IsMovingOnGround())
	{
		if(this->GetCharacterMovement()->IsMovementInProgress())
		{
			UE_LOG(LogTemp, Warning, TEXT("isMoving")); 
		} else
		{
			UE_LOG(LogTemp, Warning, TEXT("NotMoving")); 
		}
	}*/
}

void AChaseAI::MoveToWaypoints()
{

	AChaseAiController* ControllerAI = Cast<AChaseAiController>(GetController());
	if(ControllerAI)
	{
		if(CurrentWaypoint <= Waypoints.Num())
		{
			for (AActor* Waypoint : Waypoints)
			{
				AWayPoints* WaypointItr = Cast<AWayPoints>(Waypoint);

				if(WaypointItr)
				{
					if(WaypointItr->GetWaypointOrder() == CurrentWaypoint)
					{
						ControllerAI->MoveToActor(WaypointItr, 10);
						CurrentWaypoint++;
						break;
					}
				}
			}
		}
	}
	
}

// Called when the game starts or when spawned
void AChaseAI::BeginPlay()
{
	Super::BeginPlay();

	// Gets all actors in current level, and adds them to the Waypoints array
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), AWayPoints::StaticClass(), Waypoints);
	
	// Change to BTTAsk 
	MoveToWaypoints();
}

// Called every frame
void AChaseAI::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	ReportNoise(NULL,NULL);
}

// Called to bind functionality to input
void AChaseAI::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

