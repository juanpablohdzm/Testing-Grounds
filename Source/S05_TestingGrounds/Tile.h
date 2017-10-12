// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/Actor.h"
#include "Tile.generated.h"


USTRUCT()
struct FSpawnPosition
{
	GENERATED_USTRUCT_BODY()
	FVector Location;
	float Rotation;
	float Scale;
};

class UActorPool_Component;


UCLASS()
class S05_TESTINGGROUNDS_API ATile : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ATile();

	UFUNCTION(BlueprintCallable, Category = Setup)
	virtual void PlaceActors(TSubclassOf<AActor>ToSpawn, int32 MinSpawn=1, int32 MaxSpawn=1,float Radius=500, float Min_Scale=1, float Max_Scale=1);

	UFUNCTION(BlueprintCallable, Category = Setup)
	virtual void PlaceAIPawns(TSubclassOf<APawn>ToSpawn, int32 MinSpawn = 1, int32 MaxSpawn = 1, float Radius = 100);

	UPROPERTY(EditDefaultsOnly,Category=Box)
	FVector MinSpawningExtent = FVector(0, -2000, 0);

	UPROPERTY(EditDefaultsOnly, Category = Box)
	FVector MaxSpawningExtent = FVector(4000, 2000, 0);

	UPROPERTY(EditDefaultsOnly, Category = Box)
	float NavMeshOffSet_X=2000;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UFUNCTION(BlueprintCallable, Category = Setup)
	void SetupPool(UActorPool_Component * PoolToSet);

	void PositionNavMeshBoundsVolume();

private:

	//Check if the candidate point has free space to spawn
	virtual bool CanSpawnAtLocation(FVector Location, float Radius);

	//Finds a candidate point to spawn an actor 
	virtual bool FindEmptyLocation(FVector & OutLocation, float Radius);

	//Place the actor in a open checked location
	virtual void PlaceActor(TSubclassOf<AActor> ToSpawn,  FSpawnPosition SpawnPosition);

	virtual void PlaceActor(TSubclassOf<APawn> ToSpawn, FSpawnPosition SpawnPosition);

	//Creates the FBox for the Tile
	void SetTileBox();

	template<class T> void SpawnPositionsGenerator(TSubclassOf<T> ToSpawn,int32 MinSpawn, int32 MaxSpawn, float Radius, float MinScale, float MaxScale);

	FBox TileBox;

	UActorPool_Component * Pool;

	AActor * NavMeshBoundsVolume;


	//Holds the actors created every tile and get destroy when the tile is destroy 
	TArray<AActor *> Garbage;
	
};
