
#include "HealthPack.h"
#include "MazeCharacter.h"
#include "Kismet/GameplayStatics.h"
#include "NiagaraFunctionLibrary.h"

// Constructor.
AHealthPack::AHealthPack()
{
	// Restore 25 health by default.
	healthToAdd = 25.0f;

	// Enable Tick so the pickup can animate.
	PrimaryActorTick.bCanEverTick = true;
}

// Called when the player touches the Health Pack.
void AHealthPack::Apply(AMazeCharacter* Player)
{
	// Make sure we have a valid player.
	if (Player == nullptr)
	{
		return;
	}

	// Restore the player's health.
	Player->Heal(healthToAdd);

	// Play the pickup sound.
	if (PickupSound)
	{
		UGameplayStatics::PlaySoundAtLocation(
			this,
			PickupSound,
			GetActorLocation()
		);
	}

	// Spawn the green healing particle effect.
	if (HealingEffect)
	{
		// Spawn the particles 100 units above the Health Pack.
		FVector SpawnLocation = GetActorLocation();
		SpawnLocation.Z += 100.0f;

		UNiagaraFunctionLibrary::SpawnSystemAtLocation(
			GetWorld(),
			HealingEffect,
			SpawnLocation,
			FRotator::ZeroRotator,
			FVector(1.0f),
			true,
			true
		);

		UE_LOG(LogTemp, Warning,
			TEXT("Health Pack Niagara effect spawned!"));
	}

	// Print a message to the Output Log.
	UE_LOG(LogTemp, Warning,
		TEXT("Health Pack collected! Restored %f health."),
		healthToAdd);

	// Remove the Health Pack.
	DestroySelf();
}


void AHealthPack::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	// Keep track of elapsed time.
	RunningTime += DeltaTime;

	// Rotate the visible Health Pack.
	PickupMesh->AddLocalRotation(
		FRotator(0.0f, RotationSpeed * DeltaTime, 0.0f)
	);

	// Calculate smooth up-and-down movement.
	float NewHeight = FMath::Sin(
		RunningTime * FloatSpeed
	) * FloatHeight;

	// Move only the mesh, not the collision sphere.
	PickupMesh->SetRelativeLocation(
		FVector(0.0f, 0.0f, NewHeight)
	);
}



