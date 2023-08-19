// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AIBase.h"
#include "Perception/PawnSensingComponent.h"
#include "AIBase_PawnSensingComponent.generated.h"

/**
 * 
 */
UCLASS()
class PERCEPTION_API UAIBase_PawnSensingComponent : public UPawnSensingComponent
{
	GENERATED_BODY()

	UAIBase_PawnSensingComponent();

	virtual void BeginPlay() override;

	
	
};
