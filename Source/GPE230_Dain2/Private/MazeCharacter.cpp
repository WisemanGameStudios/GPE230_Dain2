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


void AMazeCharacter::Heal(float healthToAdd)
{
	// Do not heal the player if they are dead.
	if (_isDead)
	{
		return;
	}

	// Add health without exceeding maxHealth.
	_currentHealth = FMath::Clamp(
		_currentHealth + healthToAdd,
		0.0f,
		maxHealth
	);

	// Display the updated health in the Output Log.
	UE_LOG(LogTemp, Log,
		TEXT("Player healed! Current Health: %f"),
		_currentHealth);
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

void AMazeCharacter::ActivateStunParticleSystem()
{
	// Spawn a particle system and play it once
	if (_stunSystem)
	{
		USceneComponent* AttachComp = GetDefaultAttachComponent();
		
		UNiagaraComponent* NiagaraComp = UNiagaraFunctionLibrary::SpawnSystemAttached(_stunSystem, AttachComp, NAME_None,
			FVector(0), FRotator(0), EAttachLocation::Type::KeepRelativeOffset, true);
		
		NiagaraComp->Activate();
	}
	else
	{
		UE_LOG(LogTemp, Error, TEXT("Player attempted to use stun ability, but no template particle system was found"));
	}
}
