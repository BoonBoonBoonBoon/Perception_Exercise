// Fill out your copyright notice in the Description page of Project Settings.


#include "BaseAI/PreyAI/PreyAIPawn.h"

#include "AIController.h"
#include "MeshUtilitiesCommon.h"
#include "BaseAI/ChaseAI/ChaseAiController.h"
#include "BaseAI/PreyAI/AIPreyController.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Chaos/Deformable/ChaosDeformableCollisionsProxy.h"
#include "Components/PawnNoiseEmitterComponent.h"
#include "EntitySystem/MovieSceneEntitySystemRunner.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Perception/AIPerceptionStimuliSourceComponent.h"
#include "Perception/AISense_Hearing.h"
#include "Perception/AISense_Sight.h"

// Sets default values
APreyAIPawn::APreyAIPawn()
{
	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	GetCharacterMovement()->MaxWalkSpeed = 300;

	NoiseEmitter = CreateDefaultSubobject<UPawnNoiseEmitterComponent>(TEXT("PawnNoiseEmitter"));
}

void APreyAIPawn::TestDistFunc()
{
	/*
	AAIController* AIController = Cast<AAIPreyController>(Owner);
	const FVector CurrentAILoc = AIController->GetPawn()->GetActorLocation();

	AChaseAiController* PredatorCont = nullptr;
	FVector OtherAILocation = PredatorCont->GetPawn()->GetActorLocation();

	// Calculate the distance from current ai to the other AI
	float DistanceToOtherAI = FVector::Dist(CurrentAILoc, OtherAILocation);
	UE_LOG(LogTemp, Warning, TEXT("Distance to Other AI: %f"), DistanceToOtherAI);
	*/
}

void APreyAIPawn::OnOverlapBegin(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
                                 UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep,
                                 const FHitResult& SweepResult)
{
	// Maybe learn team id first...
}

void APreyAIPawn::OnOverlapEnd(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
                               UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep,
                               const FHitResult& SweepResult)
{
}

// Called when the game starts or when spawned
void APreyAIPawn::BeginPlay()
{
	Super::BeginPlay();
	SetupSphere();
	TestDistFunc();
}

void APreyAIPawn::SetupStimulusSource()
{
	// Give Specific Tag

	StimuliSourcePrey = CreateDefaultSubobject<UAIPerceptionStimuliSourceComponent>(TEXT("Stimulus Source"));
	if (StimuliSourcePrey)
	{
		StimuliSourcePrey->RegisterForSense(TSubclassOf<UAISense_Sight>());
		StimuliSourcePrey->RegisterForSense(TSubclassOf<UAISense_Hearing>());
		StimuliSourcePrey->RegisterWithPerceptionSystem();
	}
}

void APreyAIPawn::ReportNoise(USoundBase* SoundToPlay, float Volume)
{
	// Get the Velocity
	FVector ActorVelocity = GetVelocity();

	// Calculate the speed as the magnitude of the velocity vector
	float Speed = ActorVelocity.Size();

	if (Speed >= 150.f)
	{
		// Log the speed to the output
		//UE_LOG(LogTemp, Warning, TEXT("Running!"));

		//Report we played a sound at a certain volume in a specific location
		MakeNoise(Volume, this, GetActorLocation());
	}

	// report a noise
	/*if(SoundToPlay)
	{
		// Plays the actual sound
		UGameplayStatics::PlaySoundAtLocation(GetWorld(),SoundToPlay, GetActorLocation(), Volume);

		//Report we played a sound at a certain volume in a specific location
		MakeNoise(Volume, this, GetActorLocation());
	}*/
}

// Called every frame
void APreyAIPawn::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	// Makes a noise
	ReportNoise(NULL, 1);
}

// Called to bind functionality to input
void APreyAIPawn::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
}

void APreyAIPawn::SetupSphere()
{
	// Array that contains the hit results
	TArray<FHitResult> HitResults;

	// Origin
	FVector StartLocation = GetActorLocation();

	// Need to get the end location, since it isnt a single location and rather a radius we want to expand it on the Z axis
	FVector EndLocation = GetActorLocation();
	EndLocation.Z += SphereHeight;

	// Search for pawn only
	ECollisionChannel ECC = ECollisionChannel::ECC_Pawn;

	// Declare collision shape assign sphere shape and set radius
	FCollisionShape CollisionShape;
	CollisionShape.ShapeType = ECollisionShape::Sphere;
	CollisionShape.SetSphere(SphereRadius + 800);

	bool bHit = GetWorld()->SweepMultiByChannel(HitResults, StartLocation, EndLocation, FQuat(), ECC, CollisionShape);

	FVector CenterOfSphere = ((EndLocation - StartLocation) / 2) + StartLocation;

	/*Draw the sphere in the viewport*/
	DrawDebugSphere(GetWorld(), CenterOfSphere, CollisionShape.GetSphereRadius(), Segements, FColor::Blue, false);

	if (bHit)
	{
		//DrawDebugBox()
	}
}

