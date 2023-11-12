// Fill out your copyright notice in the Description page of Project Settings.


#include "BaseAI/Waypoints/WaypointTraversal.h"

// Sets default values
AWaypointTraversal::AWaypointTraversal()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AWaypointTraversal::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AWaypointTraversal::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

