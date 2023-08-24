// Fill out your copyright notice in the Description page of Project Settings.

#include "DrawDebugHelpers.h"    
#include "Kismet/GameplayStatics.h"
#include "BaseAI/CustomSensing/CustomPawnSensing.h"

#include "BaseAI/AIBase.h"
#include "Kismet/KismetSystemLibrary.h"
#include "Perception/PerceptionCharacter.h"
#include "PhysicsEngine/ShapeElem.h"

// Sets default values for this component's properties
UCustomPawnSensing::UCustomPawnSensing()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;
	
	SphereBody = CreateDefaultSubobject<USphereComponent>("SphereBody");
	SphereBody->SetupAttachment(GetAttachParent());
	
}



void UCustomPawnSensing::SensingRadius()
{
	const UWorld* World = GetWorld();
	if(World)
	{
		const FVector SphereMatrix = GetComponentLocation();
		DrawDebugSphere(GetWorld(), SphereMatrix, 800.f, 12, FColor::Blue, false
			, 0.001, 0, 1.f);

		
	//APerceptionCharacter* PerceptionCharacter = Cast<UCustomPawnSensing>();
	}
		/*const FCollisionParameters ColParam;
		const FHitResult FHit
		const FVector StartVec = GetComponentLocation();
		const FVector ForVec = VectorRound();
		const FVector EndVec;
		bool bSphere = GetWorld()->LineTraceSingleByChannel()*/
		//if(){}
}

// Called when the game starts
void UCustomPawnSensing::BeginPlay()
{
	Super::BeginPlay();

	
}


// Called every frame
void UCustomPawnSensing::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	SensingRadius();
	//SensingPeripherial();


}

/*	void SensingPeripherial();
{
	const UWorld* World = GetWorld();
	
	const FVector WorldTrans = GetComponentTransform().GetLocation();
	FVector ForwardVector = GetForwardVector();
	const float Range = 1000.f;

	//radians
	const float PawnSenseHeight = (45 / 180);
	const float PawnSenseWidth =  (90 / 180);

	const UKismetSystemLibrary* KisLib = nullptr;
	KisLib->DrawDebugCone(GetWorld(), WorldTrans,ForwardVector, Range, PawnSenseWidth, PawnSenseHeight, 12, FColor::Blue, 1.f, 1.f);

	//DrawDebugCone(GetWorld(), WorldTrans, ForwardVector, Range, PawnSenseWidth * 2.f, PawnSenseHeight * 2.f,
			  //    12, FColor::Red, true, 1, 1, 1);
	
}*/
