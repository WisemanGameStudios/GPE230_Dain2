
#pragma once

#include "CoreMinimal.h"
#include "Pickup.h"
#include "ShieldPickup.generated.h"

UCLASS()
class GPE230_DAIN2_API AShieldPickup : public APickup
{
	GENERATED_BODY()

public:

	// Constructor.
	AShieldPickup();

	// Called when the player collects the shield.
	virtual void Apply(AMazeCharacter* Player) override;
	
	// Updates the shield animation every frame.
	virtual void Tick(float DeltaTime) override;

protected:

	// How long the shield protects the player.
	UPROPERTY(EditAnywhere, Category = "Shield",
		meta = (ClampMin = "0.1"))
	float ShieldDuration = 10.0f;
	
	// Rotation speed.
	UPROPERTY(EditAnywhere, Category = "Animation")
	float RotationSpeed = 90.0f;

	// Floating height.
	UPROPERTY(EditAnywhere, Category = "Animation")
	float FloatHeight = 15.0f;

	// Floating speed.
	UPROPERTY(EditAnywhere, Category = "Animation")
	float FloatSpeed = 2.0f;
	
private:

	// Tracks the animation time.
	float RunningTime = 0.0f;
};
