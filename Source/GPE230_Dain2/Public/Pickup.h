
#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Pickup.generated.h"

// Forward declarations.
class USphereComponent;
class UStaticMeshComponent;
class AMazeCharacter;

UCLASS(Abstract)
class GPE230_DAIN2_API APickup : public AActor
{
    GENERATED_BODY()

public:

    // Constructor.
    APickup();

    // Effect applied when the player collects the pickup.
    virtual void Apply(AMazeCharacter* Player)
        PURE_VIRTUAL(APickup::Apply, );

    // Remove the pickup from the level.
    void DestroySelf();

protected:

    // Collision sphere detects the player.
    UPROPERTY(VisibleAnywhere, Category = "Pickup")
    USphereComponent* TriggerVolume;

    // Visible representation of the pickup.
    UPROPERTY(VisibleAnywhere, Category = "Pickup")
    UStaticMeshComponent* PickupMesh;

    // Called when something enters the sphere.
    UFUNCTION()
    void OnPickupOverlap(
        UPrimitiveComponent* OverlappedComponent,
        AActor* OtherActor,
        UPrimitiveComponent* OtherComp,
        int32 OtherBodyIndex,
        bool bFromSweep,
        const FHitResult& SweepResult
    );
};

