// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/Character.h"
#include "Mannequin.generated.h"

UCLASS()
class S05_TESTINGGROUNDS_API AMannequin : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AMannequin();

	/** Third  person camera */
	/*UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	class UCameraComponent* ThirdPersonCameraComponent;*/

	/** Third  person camera spring arm*/
	/*UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	class USpringArmComponent * CameraBoom;*/



///////////////////////////////////////////////////////

	/** First person camera */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	class UCameraComponent* FirstPersonCameraComponent;

	/** Pawn mesh: 1st person view (arms; seen only by self) */
	UPROPERTY(VisibleDefaultsOnly, Category = Mesh)
	class USkeletalMeshComponent* Mesh1P;

	UPROPERTY(EditDefaultsOnly, Category = "Setup")
	TSubclassOf<class AGun> GunBlueprint;

	UFUNCTION(BlueprintCallable,Category=Functions)
	void PullTrigger();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;



public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	virtual void UnPossessed() override;
private:

	void EndPlay(const EEndPlayReason::Type EndPlayReason);

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	AGun* Gun;
};
