// Fill out your copyright notice in the Description page of Project Settings.


#include "BaseAI/AIBase.h"

#include "Perception/PerceptionCharacter.h"

// Sets default values
AAIBase::AAIBase()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	Body = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Body"));
	Head = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Head"));

	Body->SetupAttachment(RootComponent);
	Head->SetupAttachment(Body);

	PawnSensing = CreateDefaultSubobject<UCustomPawnSensing>(TEXT("PawnSensing"));
	PawnSensing->SetupAttachment(Head);

	DetectionBody = CreateDefaultSubobject<USphereComponent>(TEXT("DetectionBody"));
	DetectionBody->SetupAttachment(Body);
	DetectionBody->SetSphereRadius(2000.f);
	DetectionBody->ShapeColor = FColor::Green;
	
	/*PawnSensingComponent->SetPeripheralVisionAngle(20.f);
	PawnSensingComponent->SightRadius = 1000.f;
	#1#*/
	
}


void AAIBase::OnBeginOverlap(UPrimitiveComponent* OverlapComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp,
	int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	// if OtherActor is true
	if(OtherActor)
	{
		
		UE_LOG(LogTemp, Warning, TEXT("Other Actor Valid"));

		// Tells the compiler that I want the otherActor to refrence the playerActor.
	APerceptionCharacter* PlayerRef= Cast<APerceptionCharacter>(OtherActor);
		if(PlayerRef)
		{
			UE_LOG(LogTemp, Warning, TEXT("PlayerRef Valid"));
		}
	}
}

// Called when the game starts or when spawned
void AAIBase::BeginPlay()
{
	Super::BeginPlay();
}

// Called every frame
void AAIBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	DetectionBody->OnComponentBeginOverlap.AddDynamic(this, &AAIBase::OnBeginOverlap);
}

// Called to bind functionality to input
void AAIBase::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}


