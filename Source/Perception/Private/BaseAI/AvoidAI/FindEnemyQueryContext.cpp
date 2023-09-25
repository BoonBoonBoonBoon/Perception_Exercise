// Fill out your copyright notice in the Description page of Project Settings.


#include "BaseAI/AvoidAI/FindEnemyQueryContext.h"

void UFindEnemyQueryContext::ProvideContext(FEnvQueryInstance& QueryInstance, FEnvQueryContextData& ContextData) const
{
	Super::ProvideContext(QueryInstance, ContextData);

	//Get the owner of the query and cast to an actor
	//then the actors controller and cast it to the aicontroller
	/*APreyController* AICon = Cast<APreyController>((Cast<AActor>((QueryInstance.Owner).Get())->GetInstigatorController()));

	
	if(AICon && AICon->GetSeeingPawn())
	{
		UEnvQueryItemType_Actor::SetContextHelper(ContextData, AICon->GetSeeingPawn());
	}*/
	
}
