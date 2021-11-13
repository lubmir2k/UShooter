// Fill out your copyright notice in the Description page of Project Settings.


#include "UShooterAnimInstance.h"
#include "UShooterCharacter.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Kismet/KismetMathLibrary.h"

void UUShooterAnimInstance::UpdateAnimationProperties(float DeltaTime)
{
	if(UShooterCharacter == nullptr)
	{
		UShooterCharacter = Cast<AUShooterCharacter>(TryGetPawnOwner());
	}
	if(UShooterCharacter)
	{
		// Get the lateral speed of the character from velocity
		FVector Velocity { UShooterCharacter->GetVelocity() };
		Velocity.Z = 0;
		Speed = Velocity.Size();

		// Is the character in the air?
		bIsInAir = UShooterCharacter->GetCharacterMovement()->IsFalling();

		// Is the character accelerating?
		if(UShooterCharacter->GetCharacterMovement()->GetCurrentAcceleration().Size() > 0.f)
		{
			bIsAccelerating = true;
		}
		else
		{
			bIsAccelerating = false;
		}

		FRotator AimRotation = UShooterCharacter->GetBaseAimRotation();
		//FString RotationMessage = FString::Printf(TEXT("Base Aim Rotation: %f"), AimRotation.Yaw);

		FRotator MovementRotation = UKismetMathLibrary::MakeRotFromX(UShooterCharacter->GetVelocity());
		//FString MovementRotationMessage = FString::Printf(TEXT("Movement Rotation: %f"), MovementRotation.Yaw);
		
		MovementOffsetYaw = UKismetMathLibrary::NormalizedDeltaRotator(MovementRotation, AimRotation).Yaw;
		FString MovementOffsetMessage = FString::Printf(TEXT("Movement Offset Yaw: %f"), MovementOffsetYaw);

		if(UShooterCharacter->GetVelocity().Size() > 0.f)
		{
			LastMovementOffsetYaw = MovementOffsetYaw;
		}

		/*
		if(GEngine)
		{
			GEngine->AddOnScreenDebugMessage(1, 0.f, FColor::White, MovementOffsetMessage);
		}
		*/
	}
}

void UUShooterAnimInstance::NativeInitializeAnimation()
{
	UShooterCharacter = Cast<AUShooterCharacter>(TryGetPawnOwner()); // Returns a Pawn, casts it to AShooter character and store it in the ShooterCharacter pointer
}

