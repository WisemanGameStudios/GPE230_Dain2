
#include "HealthPack.h"
#include "MazeCharacter.h"
#include "Kismet/GameplayStatics.h"
#include "NiagaraFunctionLibrary.h"
#include "Components/CapsuleComponent.h"

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

    // Spawn healing particles around the player.
    if (HealingEffect)
    {
        // Attach the particles to the player's capsule.
        // This allows the effect to follow the player.
        UNiagaraFunctionLibrary::SpawnSystemAttached(
            HealingEffect,
            Player->GetCapsuleComponent(),
            NAME_None,
            FVector::ZeroVector,
            FRotator::ZeroRotator,
            EAttachLocation::KeepRelativeOffset,
            true,
            true
        );

        UE_LOG(LogTemp, Warning,
            TEXT("Healing particles attached to player!"));
    }

    // Print a message to the Output Log.
    UE_LOG(LogTemp, Warning,
        TEXT("Health Pack collected! Restored %f health."),
        healthToAdd);

    // Remove the Health Pack.
    DestroySelf();
}

// Animate the Health Pack.
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



