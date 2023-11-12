// Copyright Epic Games, Inc. All Rights Reserved.

#include "PerceptionCharacter.h"
#include "Camera/CameraComponent.h"
#include "Components/CapsuleComponent.h"
#include "Components/InputComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/Controller.h"
#include "GameFramework/SpringArmComponent.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "BaseAI/AIBase.h"
#include "Components/PawnNoiseEmitterComponent.h"
#include "DSP/Osc.h"
#include "Kismet/GameplayStatics.h"
#include "Perception/AIPerceptionStimuliSourceComponent.h"
#include "Perception/AISense_Hearing.h"
#include "Perception/AISense_Sight.h"


//////////////////////////////////////////////////////////////////////////
// APerceptionCharacter

APerceptionCharacter::APerceptionCharacter()
{
	// Set size for collision capsule
	GetCapsuleComponent()->InitCapsuleSize(42.f, 96.0f);
		
	// Don't rotate when the controller rotates. Let that just affect the camera.
	bUseControllerRotationPitch = false;
	bUseControllerRotationYaw = false;
	bUseControllerRotationRoll = false;

	// Configure character movement
	GetCharacterMovement()->bOrientRotationToMovement = true; // Character moves in the direction of input...	
	GetCharacterMovement()->RotationRate = FRotator(0.0f, 500.0f, 0.0f); // ...at this rotation rate

	// Note: For faster iteration times these variables, and many more, can be tweaked in the Character Blueprint
	// instead of recompiling to adjust them
	GetCharacterMovement()->JumpZVelocity = 700.f;
	GetCharacterMovement()->AirControl = 0.35f;
	GetCharacterMovement()->MaxWalkSpeed = 500.f;
	GetCharacterMovement()->MinAnalogWalkSpeed = 20.f;
	GetCharacterMovement()->BrakingDecelerationWalking = 2000.f;

	// Create a camera boom (pulls in towards the player if there is a collision)
	CameraBoom = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraBoom"));
	CameraBoom->SetupAttachment(RootComponent);
	CameraBoom->TargetArmLength = 400.0f; // The camera follows at this distance behind the character	
	CameraBoom->bUsePawnControlRotation = true; // Rotate the arm based on the controller

	// Create a follow camera
	FollowCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("FollowCamera"));
	FollowCamera->SetupAttachment(CameraBoom, USpringArmComponent::SocketName); // Attach the camera to the end of the boom and let the boom adjust to match the controller orientation
	FollowCamera->bUsePawnControlRotation = false; // Camera does not rotate relative to arm

	// Note: The skeletal mesh and anim blueprint references on the Mesh component (inherited from Character) 
	// are set in the derived blueprint asset named ThirdPersonCharacter (to avoid direct content references in C++)

	Collision = CreateDefaultSubobject<USphereComponent>("Collision");
	Collision->SetupAttachment(RootComponent);

	// Noise Emitter to make sound 
	NoiseEmitter = CreateDefaultSubobject<UPawnNoiseEmitterComponent>(TEXT("PawnNoiseEmitter"));

	// Assigns the character to the team of 1
	TeamId = FGenericTeamId(1);
	VolumeOutput = 1.f;
	Tags.Add(TEXT("Player"));
}

// Stim for ai
void APerceptionCharacter::SetupStimulusSource()
{
	StimuliSource = CreateDefaultSubobject<UAIPerceptionStimuliSourceComponent>(TEXT("Stimulus Source"));
	if(StimuliSource)
	{
		StimuliSource->RegisterForSense(TSubclassOf<UAISense_Sight>());
		StimuliSource->RegisterForSense(TSubclassOf<UAISense_Hearing>());
		StimuliSource->RegisterWithPerceptionSystem();
	}
}

void APerceptionCharacter::ReportNoise(USoundBase* SoundToPlay, float Volume)
{
	// If the USound is valid, Play it and report it to the game.
	if(SoundToPlay)
	{
		// Plays the actual sound
		UGameplayStatics::PlaySoundAtLocation(GetWorld(),SoundToPlay, GetActorLocation(), Volume);

		//Report we played a sound at a certain volume in a specific location
		MakeNoise(Volume, this, GetActorLocation());
	}
}



void APerceptionCharacter::MoveForward(float value)
{
	if (value != 0)
	{
		VolumeOutput = 1.f;
		AddMovementInput(GetActorForwardVector(), value);
	}
}

void APerceptionCharacter::MoveSide(float Value)
{
	if(Value != 0)
	{
		AddMovementInput(GetActorRightVector(), Value);
	}
}

void APerceptionCharacter::OnBeginOverlap(UPrimitiveComponent* OverlapComponent, AActor* OtherActor,
                                          UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (OtherActor)
	{
		AAIBase* Ref = Cast<AAIBase>(OtherActor);
		if(Ref)
		{
			UE_LOG(LogTemp, Warning, TEXT("Hit"));
		}
	}


	
}

void APerceptionCharacter::BeginPlay()
{
	// Call the base class  
	Super::BeginPlay();

	//Add Input Mapping Context
	if (APlayerController* PlayerController = Cast<APlayerController>(Controller))
	{
		if (UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(PlayerController->GetLocalPlayer()))
		{
			Subsystem->AddMappingContext(DefaultMappingContext, 0);
		}
	}
}

void APerceptionCharacter::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);

	Collision->OnComponentBeginOverlap.AddDynamic(this, &APerceptionCharacter::OnBeginOverlap);
}

//////////////////////////////////////////////////////////////////////////
// Input

void APerceptionCharacter::SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent)
{
	// Set up action bindings
	if (UEnhancedInputComponent* EnhancedInputComponent = CastChecked<UEnhancedInputComponent>(PlayerInputComponent)) {
		
		//Jumping
		EnhancedInputComponent->BindAction(JumpAction, ETriggerEvent::Triggered, this, &ACharacter::Jump);
		EnhancedInputComponent->BindAction(JumpAction, ETriggerEvent::Completed, this, &ACharacter::StopJumping);

		//Moving
		EnhancedInputComponent->BindAction(MoveAction, ETriggerEvent::Triggered, this, &APerceptionCharacter::Move);

		//Looking
		EnhancedInputComponent->BindAction(LookAction, ETriggerEvent::Triggered, this, &APerceptionCharacter::Look);

	}

	/*
	PlayerInputComponent->BindAxis("MoveForward", this, &APerceptionCharacter::MoveForward);
	PlayerInputComponent->BindAxis("MoveSide", this, &APerceptionCharacter::MoveSide);
	
	// Mouse Input
	PlayerInputComponent->BindAxis("Look Down / Look Up", this, &APawn::AddControllerPitchInput);
	PlayerInputComponent->BindAxis("Look RIght / Look Left", this, &APawn::AddControllerYawInput);
	*/

}

void APerceptionCharacter::Move(const FInputActionValue& Value)
{
	// input is a Vector2D
	FVector2D MovementVector = Value.Get<FVector2D>();

	if (Controller != nullptr)
	{
		// find out which way is forward
		const FRotator Rotation = Controller->GetControlRotation();
		const FRotator YawRotation(0, Rotation.Yaw, 0);

		// get forward vector
		const FVector ForwardDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);
	
		// get right vector 
		const FVector RightDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);

		// add movement 
		AddMovementInput(ForwardDirection, MovementVector.Y);
		AddMovementInput(RightDirection, MovementVector.X);
	}
}

void APerceptionCharacter::Look(const FInputActionValue& Value)
{
	// input is a Vector2D
	FVector2D LookAxisVector = Value.Get<FVector2D>();

	if (Controller != nullptr)
	{
		// add yaw and pitch input to controller
		AddControllerYawInput(LookAxisVector.X);
		AddControllerPitchInput(LookAxisVector.Y);
	}
}




