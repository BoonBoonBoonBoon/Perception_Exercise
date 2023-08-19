// Fill out your copyright notice in the Description page of Project Settings.


#include "FoodContent/Grass_Food.h"

// Sets default values
AGrass_Food::AGrass_Food()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	SkeletalMeshComponent=  CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("SkeletalMesh"));
	Collision = CreateDefaultSubobject<USphereComponent>(TEXT("Collison"));

	Collision->SetupAttachment(SkeletalMeshComponent);
	Collision->SetSphereRadius(80.f);
	
	
}

// Called when the game starts or when spawned
void AGrass_Food::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AGrass_Food::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

