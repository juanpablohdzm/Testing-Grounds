// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Components/ActorComponent.h"
#include "ActorPool_Component.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class S05_TESTINGGROUNDS_API UActorPool_Component : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UActorPool_Component();

	AActor * Checkout();
	
	void Return(AActor * ActorToReturn);
	
	void Add(AActor * ActorToAdd);
private:
	TArray<AActor*> Pool;
	
};
