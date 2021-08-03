// Fill out your copyright notice in the Description page of Project Settings.


#include "ShooterAnimInstance.h"
#include "ShooterCharacter.h"
#include "GameFramework/CharacterMovementComponent.h"

void UShooterAnimInstance::UpdateAnimationProperties(float DeltaTime)
{
	if (UShooterCharacter == nullptr)
	{
		UShooterCharacter = Cast<AShooterCharacter>(TryGetPawnOwner());
	}
	if (UShooterCharacter)
	{
		// Get the lateral speed of the character from velocity
		FVector Velocity{ UShooterCharacter->GetVelocity() };
		Velocity.Z = 0;
		Speed = Velocity.Size();

		// Is the character in the air?
		bIsInAir = UShooterCharacter->GetCharacterMovement()->IsFalling();

		// Is the character accelerating?
		if (UShooterCharacter->GetCharacterMovement()->GetCurrentAcceleration().Size() > 0.f)
		{
			bIsAccelerating = true;
		}
		else
		{
			bIsAccelerating = false;
		}
	}
}

void UShooterAnimInstance::NativeInitializeAnimation()
{
	UShooterCharacter = Cast<AShooterCharacter>(TryGetPawnOwner());
}