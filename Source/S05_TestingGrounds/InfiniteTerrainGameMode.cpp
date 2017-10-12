// Fill out your copyright notice in the Description page of Project Settings.

#include "S05_TestingGrounds.h"
#include "InfiniteTerrainGameMode.h"
#include "AI/Navigation/NavMeshBoundsVolume.h"
#include "ActorPool_Component.h"
#include "EngineUtils.h"

AInfiniteTerrainGameMode::AInfiniteTerrainGameMode()
{
	NavMeshBoundsVolumePool = CreateDefaultSubobject<UActorPool_Component>(FName("NMBV Pool"));
}

void AInfiniteTerrainGameMode::PopulateBoundsVolumePool()
{
	TActorIterator<ANavMeshBoundsVolume> VolumeIterator = TActorIterator<ANavMeshBoundsVolume>(GetWorld());
	while (VolumeIterator)
	{
		AddToPool(*VolumeIterator);
		++VolumeIterator;
	}
	
}

void AInfiniteTerrainGameMode::AddToPool( ANavMeshBoundsVolume * VolumeToAdd)
{
	NavMeshBoundsVolumePool->Add(VolumeToAdd);
}


