// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "NiagaraFunctionLibrary.h"
#include "NiagaraComponent.h"
#include "MazeCharacter.generated.h"

UCLASS()
class GPE230_DAIN2_API AMazeCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AMazeCharacter();
	
	// Restore health when collecting a Health Pack.
	UFUNCTION(BlueprintCallable, Category = "Health")
	void Heal(float healthToAdd);
	
	// Return the player's current health.
	UFUNCTION(BlueprintPure, Category = "Health")
	float GetCurrentHealth() const
	{
		return _currentHealth;
	}

	// Return health as a percentage from 0 to 1.
	UFUNCTION(BlueprintPure, Category = "Health")
	float GetHealthPercent() const
	{
		if (maxHealth <= 0.0f)
		{
			return 0.0f;
		}

		return FMath::Clamp(
			_currentHealth / maxHealth,
			0.0f,
			1.0f
		);
	}
	
	// Starting Health
	UPROPERTY(EditAnywhere)
	float maxHealth;
	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
	


protected:
	// Current health of player
	float _currentHealth;
	
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	
	virtual float TakeDamage(float DamageAmount, struct FDamageEvent const& DamageEvent, class AController* EventInstigator, AActor* DamageCauser) override;
	
	virtual void Die();
	
	
	// Animation to play when player dies
	UPROPERTY(EditAnywhere)
		UAnimSequence* _deathAnim;
	
	bool _isDead = false;
	
private:
	UPROPERTY(EditAnywhere)
		UNiagaraSystem* _stunSystem;
	
	UFUNCTION(BlueprintCallable)
	void ActivateStunParticleSystem();
};
