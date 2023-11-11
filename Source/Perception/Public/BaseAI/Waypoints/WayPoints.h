// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/StaticMeshActor.h"
#include "WayPoints.generated.h"

/**
 * 
 */
UCLASS()
class PERCEPTION_API AWayPoints : public AStaticMeshActor
{
	GENERATED_BODY()
public:
	int GetWaypointOrder();

private:
	UPROPERTY(EditAnywhere, meta = (AllowPrivateAccess = "true"))
	int WaypointOrder;

	
};
