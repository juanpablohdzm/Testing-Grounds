// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "S05_TestingGroundsGameMode.h"
#include "EngineUtils.h"
#include "InfiniteTerrainGameMode.generated.h"

/**
 * 
 */
UCLASS()
class S05_TESTINGGROUNDS_API AInfiniteTerrainGameMode : public AS05_TestingGroundsGameMode
{
	GENERATED_BODY()

		AInfiniteTerrainGameMode();

public:
	UFUNCTION(BlueprintCallable,Category=BoundsPool)
	void PopulateBoundsVolumePool();

protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Pool)
	class UActorPool_Component * NavMeshBoundsVolumePool;
private:
	void AddToPool(class ANavMeshBoundsVolume * VolumeToAdd);
};
