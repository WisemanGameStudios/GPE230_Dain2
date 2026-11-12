// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "MazeCharacter.generated.h"

UCLASS()
class GPE230_DAIN2_API AMazeCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AMazeCharacter();
	
	// Starting Health
	UPROPERTY(EditAnywhere)
	float maxHealth;

protected:
	// Current health of player
	float _currentHealth;
	
	// Controls how fast our character moves.
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Movement")
	float _moveSpeed = 600.0f;

	// Controls how fast our character rotates.
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Movement")
	float _rotationSpeed = 100.0f;
	
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	
	virtual float TakeDamage(float DamageAmount, struct FDamageEvent const& DamageEvent, class AController* EventInstigator, AActor* DamageCauser) override;
	
	virtual void Die();

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

};
