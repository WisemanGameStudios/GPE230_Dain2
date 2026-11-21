
#include "ShieldPickup.h"
#include "MazeCharacter.h"

// Constructor.
AShieldPickup::AShieldPickup()
{
	ShieldDuration = 10.0f;

	// Enable animation.
	PrimaryActorTick.bCanEverTick = true;
}

// Called when the player collects the shield.
void AShieldPickup::Apply(AMazeCharacter* Player)
{
	// Make sure the player is valid.
	if (Player == nullptr)
	{
		return;
	}

	// Activate the player's temporary shield.
	Player->ActivateShield(ShieldDuration);

	// Print a message to the Output Log.
	UE_LOG(LogTemp, Warning, TEXT("Shield collected!"));

	// Remove the pickup from the maze.
	DestroySelf();
}

// Animate the shield pickup.
void AShieldPickup::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	// Track elapsed time.
	RunningTime += DeltaTime;

	// Rotate the shield mesh.
	PickupMesh->AddLocalRotation(
		FRotator(0.0f, RotationSpeed * DeltaTime, 0.0f)
	);

	// Calculate smooth floating movement.
	float NewHeight = FMath::Sin(
		RunningTime * FloatSpeed
	) * FloatHeight;

	// Move the mesh without moving the collision.
	PickupMesh->SetRelativeLocation(
		FVector(0.0f, 0.0f, NewHeight)
	);
}