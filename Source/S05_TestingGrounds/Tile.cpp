// Fill out your copyright notice in the Description page of Project Settings.

#include "S05_TestingGrounds.h"
#include "ActorPool_Component.h"
#include "Tile.h"
#include "DrawDebugHelpers.h"


// Sets default values
ATile::ATile()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;
	SetTileBox();
}

// Called when the game starts or when spawned
void ATile::BeginPlay()
{
	Super::BeginPlay();
	
}

void ATile::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	if (!ensure(NavMeshBoundsVolume)) { return; }
	Pool->Return(NavMeshBoundsVolume);
	if (Garbage.Num()!=0)
	{
		AActor * Prop;
		while (Garbage.Num() != 0)
		{
			Prop = Garbage.Pop();
			Prop->Destroy();

		}
	}
	
}

// Called every frame
void ATile::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ATile::SetupPool(UActorPool_Component * PoolToSet)
{
	Pool = PoolToSet;
	PositionNavMeshBoundsVolume();
}

void ATile::PositionNavMeshBoundsVolume()
{
	NavMeshBoundsVolume = Pool->Checkout();
	if (!ensure(NavMeshBoundsVolume)) {  UE_LOG(LogTemp, Warning, TEXT("No Pool"));return;}
	FVector NavMLocation = GetActorLocation();
	NavMLocation.X += NavMeshOffSet_X;
	NavMeshBoundsVolume->SetActorLocation(NavMLocation);
	GetWorld()->GetNavigationSystem()->Build();
}


void ATile::SetTileBox()
{
	TileBox = FBox(MinSpawningExtent, MaxSpawningExtent);
}

void ATile::PlaceAIPawns(TSubclassOf<APawn>ToSpawn, int32 MinSpawn, int32 MaxSpawn , float Radius)
{
	 SpawnPositionsGenerator(ToSpawn,MinSpawn, MaxSpawn, Radius, 1, 1);
	
}


void ATile::PlaceActors(TSubclassOf<AActor>ToSpawn,int32 MinSpawn,int32 MaxSpawn, float Radius, float MinScale, float MaxScale)
{
	SpawnPositionsGenerator(ToSpawn,MinSpawn,  MaxSpawn,  Radius,  MinScale,  MaxScale);
	
}

template<class T>
void ATile::SpawnPositionsGenerator(TSubclassOf<T> ToSpawn,int32 MinSpawn, int32 MaxSpawn, float Radius, float MinScale, float MaxScale)
{
	
	int32 NumberSpawn = FMath::RandRange(MinSpawn, MaxSpawn);
	for (int i = 0; i < NumberSpawn; i++)
	{
		FSpawnPosition SpawnPosition;
		SpawnPosition.Scale = FMath::RandRange(MinScale, MaxScale);
		bool EmptyLocation = FindEmptyLocation(SpawnPosition.Location, Radius* SpawnPosition.Scale);
		if (EmptyLocation)
		{
			
			SpawnPosition.Rotation = FMath::RandRange(-180.f, 180.f);
			PlaceActor(ToSpawn, SpawnPosition);
		}
	}	
	
	
}

bool  ATile::FindEmptyLocation(FVector & OutLocation, float Radius)
{
	const int32 MAX_ATTEMPTS = 100;
	for (int32 i = 0; i < MAX_ATTEMPTS; i++)
	{
		FVector CandidatePoint = FMath::RandPointInBox(TileBox);
		if (CanSpawnAtLocation(CandidatePoint, Radius))
		{
			
			OutLocation = CandidatePoint;
			return true;
		}
	}
	return false;
}

 void ATile::PlaceActor(TSubclassOf<APawn> ToSpawn, FSpawnPosition SpawnPosition)
{
	 SpawnPosition.Location.Z += 150;
	 FRotator NewRotation = FRotator(0, SpawnPosition.Rotation, 0);
	 APawn * Spawned = GetWorld()->SpawnActor<APawn>(ToSpawn, SpawnPosition.Location, NewRotation);
	 if (Spawned)
	 {
		 Garbage.Add(Spawned);
		 Spawned->SetActorScale3D(FVector(SpawnPosition.Scale));
		 Spawned->AttachToActor(this, FAttachmentTransformRules(EAttachmentRule::KeepRelative, false));
		 Spawned->SpawnDefaultController();
		 Spawned->Tags.Add(FName("Friend"));
	 }
}

 void ATile::PlaceActor(TSubclassOf<AActor> ToSpawn, FSpawnPosition SpawnPosition)
 {
	
	 AActor * Spawned = GetWorld()->SpawnActor(ToSpawn);
	 if (Spawned)
	 {
		 Garbage.Add(Spawned);
		 Spawned->SetActorScale3D(FVector(SpawnPosition.Scale));
		 Spawned->AttachToActor(this, FAttachmentTransformRules(EAttachmentRule::KeepRelative, false));
		 Spawned->SetActorRotation(FRotator(0, SpawnPosition.Rotation, 0));
		 Spawned->SetActorRelativeLocation(SpawnPosition.Location);
		 
	}
}

bool ATile::CanSpawnAtLocation(FVector Location, float Radius)
{
	FHitResult HitResult;
	FVector GlobalLocation = ActorToWorld().TransformPosition(Location);
	bool HasHit = GetWorld()->SweepSingleByChannel(
		HitResult,
		GlobalLocation,
		GlobalLocation,
		FQuat::Identity,
		ECollisionChannel::ECC_GameTraceChannel2,
		FCollisionShape::MakeSphere(Radius));
	
	//FColor ColorResult=HasHit ? FColor::Red : FColor::Green;
	//DrawDebugCapsule(GetWorld(), GlobalLocation, 0,Radius,FQuat::Identity, ColorResult, true, 5000);

	return !HasHit;
}
