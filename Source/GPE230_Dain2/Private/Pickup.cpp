
#include "Pickup.h"
#include "MazeCharacter.h"
#include "Components/SphereComponent.h"
#include "Components/StaticMeshComponent.h"

// Constructor.
APickup::APickup()
{
	PrimaryActorTick.bCanEverTick = false;

	// Create the collision sphere.
	TriggerVolume = CreateDefaultSubobject<USphereComponent>(
		TEXT("TriggerVolume")
	);

	RootComponent = TriggerVolume;

	// Set the pickup detection radius.
	TriggerVolume->SetSphereRadius(75.0f);

	// Detect overlaps without blocking movement.
	TriggerVolume->SetCollisionProfileName(
		TEXT("Trigger")
	);

	// Create the visible mesh.
	PickupMesh = CreateDefaultSubobject<UStaticMeshComponent>(
		TEXT("PickupMesh")
	);

	PickupMesh->SetupAttachment(RootComponent);

	// Mesh should not block the player.
	PickupMesh->SetCollisionEnabled(
		ECollisionEnabled::NoCollision
	);

	// Connect the overlap event.
	TriggerVolume->OnComponentBeginOverlap.AddDynamic(
		this,
		&APickup::OnPickupOverlap
	);
}

// Detect when the player touches the pickup.
void APickup::OnPickupOverlap(
	UPrimitiveComponent* OverlappedComponent,
	AActor* OtherActor,
	UPrimitiveComponent* OtherComp,
	int32 OtherBodyIndex,
	bool bFromSweep,
	const FHitResult& SweepResult
)
{
	// Check whether the overlapping actor is our player.
	AMazeCharacter* Player = Cast<AMazeCharacter>(
		OtherActor
	);

	if (Player)
	{
		// Apply the pickup effect.
		Apply(Player);
	}
}

// Destroy the pickup after collection.
void APickup::DestroySelf()
{
	Destroy();
}

