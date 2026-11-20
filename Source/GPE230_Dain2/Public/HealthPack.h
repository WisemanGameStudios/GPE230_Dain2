
#pragma once

#include "CoreMinimal.h"
#include "Pickup.h"
#include "HealthPack.generated.h"

class USoundBase;
class UNiagaraSystem;
UCLASS()
class GPE230_DAIN2_API AHealthPack : public APickup
{
	GENERATED_BODY()

public:

	// Constructor.
	AHealthPack();

	// Apply the health pack effect to the player.
	virtual void Apply(AMazeCharacter* Player) override;
	
	// Called every frame to animate the Health Pack.
	virtual void Tick(float DeltaTime) override;

protected:

	// Amount of health this pickup restores.
	UPROPERTY(EditAnywhere, Category = "Health Pack")
	float healthToAdd = 25.0f;
	
	
	// How fast the Health Pack rotates.
	UPROPERTY(EditAnywhere, Category = "Animation")
	float RotationSpeed = 60.0f;

	// How high the Health Pack floats.
	UPROPERTY(EditAnywhere, Category = "Animation")
	float FloatHeight = 15.0f;

	// How quickly the Health Pack floats.
	UPROPERTY(EditAnywhere, Category = "Animation")
	float FloatSpeed = 2.0f;
	
	// Sound played when the Health Pack is collected.
	UPROPERTY(EditAnywhere, Category = "Health Pack Effects")
	USoundBase* PickupSound = nullptr;

	// Niagara effect played when collected.
	UPROPERTY(EditAnywhere, Category = "Health Pack Effects")
	UNiagaraSystem* HealingEffect = nullptr;

private:

	// Tracks the floating animation.
	float RunningTime = 0.0f;

	// Original position of the visible mesh.
	FVector StartingLocation;

};
