// Fill out your copyright notice in the Description page of Project Settings.
#include "MazeCharacter.h"
#include "GameFramework/PlayerController.h"
#include "GameFramework/CharacterMovementComponent.h"

// Sets default values
AMazeCharacter::AMazeCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AMazeCharacter::BeginPlay()
{
	Super::BeginPlay();
	_currentHealth = maxHealth;
}

// Called every frame
void AMazeCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void AMazeCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

float AMazeCharacter::TakeDamage(float DamageAmount,FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser)
{
	if (!_isDead)
	{
		// Subtract Damage
		_currentHealth -= DamageAmount;
	
		UE_LOG(LogTemp, Log, TEXT("TakeDamage: %f.  %f Health Remaining"), DamageAmount, _currentHealth);
	
		// Check if you died
		if (_currentHealth <= 0)
			Die();
	
		return DamageAmount;
	}
	else
	{
		return 0;
	}
}

void AMazeCharacter::Die()
{
	_isDead = true;
	_currentHealth = 0;
	
	// Stop All Movement
	GetCharacterMovement()->MaxWalkSpeed = 0.0f;
	
	// Disable mouse look when dead.
	if (APlayerController* PC = Cast<APlayerController>(GetController()))
	{
		PC->SetIgnoreLookInput(true);
	}
	
	GetMesh()->PlayAnimation(_deathAnim, false);
	
	// ToDo: Trigger game over 
}