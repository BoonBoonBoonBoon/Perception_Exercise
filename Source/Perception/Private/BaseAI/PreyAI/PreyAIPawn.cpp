// Fill out your copyright notice in the Description page of Project Settings.


#include "BaseAI/PreyAI/PreyAIPawn.h"

#include "MeshUtilitiesCommon.h"
#include "Chaos/Deformable/ChaosDeformableCollisionsProxy.h"
#include "Components/PawnNoiseEmitterComponent.h"
#include "EntitySystem/MovieSceneEntitySystemRunner.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Perception/AIPerceptionStimuliSourceComponent.h"
#include "Perception/AISense_Hearing.h"
#include "Perception/AISense_Sight.h"

// Sets default values
APreyAIPawn::APreyAIPawn()
{
	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	GetCharacterMovement()->MaxWalkSpeed = 300;

	// Radius Detection 
	RadiusSphere = CreateDefaultSubobject<USphereComponent>("RadiusSphere");
	RadiusSphere->SetupAttachment(RootComponent);
	RadiusSphere->SetSphereRadius(1000.f);

	NoiseEmitter = CreateDefaultSubobject<UPawnNoiseEmitterComponent>(TEXT("PawnNoiseEmitter"));

	RadiusSphere->OnComponentBeginOverlap.AddDynamic(this, &APreyAIPawn::OnOverlapBegin);
	//RadiusSphere->OnComponentEndOverlap.AddDynamic(this, &APreyAIPawn::OnOverlapEnd);
}

void APreyAIPawn::OnOverlapBegin(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	// Maybe learn team id first...
	
}

void APreyAIPawn::OnOverlapEnd(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
}

// Called when the game starts or when spawned
void APreyAIPawn::BeginPlay()
{
	Super::BeginPlay();
	SetupSphere();
}

void APreyAIPawn::SetupStimulusSource()
{

	// Give Specific Tag
	
	StimuliSourcePrey = CreateDefaultSubobject<UAIPerceptionStimuliSourceComponent>(TEXT("Stimulus Source"));
	if(StimuliSourcePrey)
	{
		StimuliSourcePrey->RegisterForSense(TSubclassOf<UAISense_Sight>());
		StimuliSourcePrey->RegisterForSense(TSubclassOf<UAISense_Hearing>());
		StimuliSourcePrey->RegisterWithPerceptionSystem();
	}
	
}

void APreyAIPawn::ReportNoise(USoundBase* SoundToPlay, float Volume)
{
	// report a noise 
}

// Called every frame
void APreyAIPawn::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	//SetupSphere();
	
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
	
	if(bHit)
	{
		//DrawDebugBox()
	}
}

