// Fill out your copyright notice in the Description page of Project Settings.

#include "S05_TestingGrounds.h"
#include "ActorPool_Component.h"


// Sets default values for this component's properties
UActorPool_Component::UActorPool_Component()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = false;
}


AActor * UActorPool_Component::Checkout()
{
	if (Pool.Num() <= 0) { return nullptr; }
	return Pool.Pop();
}

void UActorPool_Component::Return(AActor * ActorToReturn)
{
	Add(ActorToReturn);
}

void UActorPool_Component::Add(AActor * ActorToAdd)
{
	Pool.Push(ActorToAdd);
}

