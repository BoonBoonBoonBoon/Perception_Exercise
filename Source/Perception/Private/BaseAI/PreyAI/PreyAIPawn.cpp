// Fill out your copyright notice in the Description page of Project Settings.


#include "BaseAI/PreyAI/PreyAIPawn.h"

#include "MeshUtilitiesCommon.h"
#include "Chaos/Deformable/ChaosDeformableCollisionsProxy.h"
#include "EntitySystem/MovieSceneEntitySystemRunner.h"
#include "GameFramework/CharacterMovementComponent.h"

// Sets default values
APreyAIPawn::APreyAIPawn()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	GetCharacterMovement()->MaxWalkSpeed = 300;
}

// Called when the game starts or when spawned
void APreyAIPawn::BeginPlay()
{
	Super::BeginPlay();
	SetupSphere();
}

// Called every frame
void APreyAIPawn::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

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
	CollisionShape.SetSphere(SphereRadius);
	
	bool bHit = GetWorld()->SweepMultiByChannel(HitResults, StartLocation, EndLocation, FQuat(), ECC, CollisionShape);

	/*If the raycast hit a number of objects, iterate through them and print their name in the console*/
	if (bHit)
	{
		for (auto It = HitResults.CreateIterator(); It; It++)
		{
			GLog->Log((*It).Actor->GetName());
		}
	}

	FVector CenterOfSphere = ((EndLocation - StartLocation) / 2) + StartLocation;
 
	/*Draw the sphere in the viewport*/
	DrawDebugSphere(GetWorld(), CenterOfSphere, CollisionShape.GetSphereRadius(), 100, FColor::Blue, true);
 
}

