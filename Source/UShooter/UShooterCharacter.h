// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "UShooterCharacter.generated.h"

UCLASS()
class USHOOTER_API AUShooterCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AUShooterCharacter();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	/* Called for forwards / backwards input */
	void MoveForward(float Value);

	/* Called for side to side input */
	void MoveRight(float Value);

	/**
	* Called via input to turn at a given rate.
	* @param Rate This is a normalized rate, i.e. 1.0 means 100% of desired turn rate
	*/
	void TurnAtRate(float Rate);

	/**
	* Called via input to look up/down at a given rate.
	* @param Rate This is a normalized rate, i.e. 1.0 means 100% of desired rate
	*/
	void LookUpAtRate(float Rate);

	/* Called when the Fire Button is pressed */
	void FireWeapon();

	bool GetBeamEndLocation(const FVector& MuzzleSocketLocation, FVector& OutBeamLocation);

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

private:
	/* Camera boom positioning the camera behind the character */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess ="true"))
	class USpringArmComponent* CameraBoom;

	/* Camera that follows the character */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	class UCameraComponent* FollowCamera;

	/** Base turn rate, in degrees per second - other scaling may affect final turn rate */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	float BaseTurnRate;

	/** Base look up/down rate, in degrees per second - other scaling may affect final turn rate */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	float BaseLookUpRate;

	/** Randomized gunshot sound */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Combat, meta = (AllowPrivateAccess = "true"))
	class USoundCue* FireSound;

	/* Flash spawn at BarrelSocket */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Combat, meta = (AllowPrivateAccess = "true"))
	class UParticleSystem* MuzzleFlash;
	
	/* Montage for firing the weapon */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Combat, meta = (AllowPrivateAccess = "true"))
	class UAnimMontage* HipFireMontage;

	/* Particles spawned upon bullet impact */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Combat, meta = (AllowPrivateAccess = "true"))
	UParticleSystem* ImpactParticles;

	/* Smoke trail for bullets */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Combat, meta = (AllowPrivateAccess = "true"))
	UParticleSystem* BeamParticles;
	
public:
	/* Returns CameraBoom subobject */
	FORCEINLINE USpringArmComponent* GetCameraBoom() const { return CameraBoom; }

	/* Returns Follow Camera subobject */
	FORCEINLINE UCameraComponent* GetFollowCamera() const { return FollowCamera; }
};
