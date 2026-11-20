// Fill out your copyright notice in the Description page of Project Settings.


#include "NPCEnemy.h"
#include "MazeCharacter.h"
#include "Kismet/KismetSystemLibrary.h"
#include "Kismet/GameplayStatics.h"
#include "GameFramework/DamageType.h"

void ANPCEnemy::DetectHit()
{
	
	UE_LOG(LogTemp, Warning,
	TEXT("ENEMY ATTACK: DetectHit was called!"));
	
	bool canDamage = true;
	
	// Get fist location 
	const FVector PunchLocation = GetMesh()->GetSocketLocation(_PunchingHandSocketName);
	
	// Don't detect actor or controller in trace
	TArray<AActor*> ActorsToIgnore;
	ActorsToIgnore.Add(this);
	ActorsToIgnore.Add(GetOwner());
	
	// Array for Actors hit by trace
	TArray<FHitResult> HitArray;
	
	// Trace around fist for overlapping actors
	const bool Hit = UKismetSystemLibrary::SphereTraceMulti(GetWorld(), PunchLocation, PunchLocation, _TraceRadius, 
		UEngineTypes::ConvertToTraceType(ECC_Camera), false, ActorsToIgnore, 
		EDrawDebugTrace::None, HitArray, true,FLinearColor::Red, FLinearColor::Green, 2.0f
		);
	
	UE_LOG(LogTemp, Warning, TEXT("SPHERE TRACE HIT: %s"),
	Hit ? TEXT("TRUE") : TEXT("FALSE"));
	
	// Debugging name of this actor
	FString ownerName = this->GetName();
	
	if (Hit)
	{
		// For each Object Hit
		for (const FHitResult &HitResult : HitArray)
		{
			if (canDamage && Cast<AMazeCharacter>(HitResult.GetActor()))
			{
				FString hitActorName = HitResult.GetActor()->GetName();

				// Print the actor names and damage amount
				UE_LOG(LogTemp, Log, TEXT("NPCEnemy actor \"%s\" hit other actor \"%s\", dealing %f damage"),
					*ownerName, *hitActorName, _HitDamage);

				/// Apply damage to the actor that was hit.
				float DamageApplied = UGameplayStatics::ApplyDamage(
					HitResult.GetActor(),
					_HitDamage,
					GetController(),
					this,
					UDamageType::StaticClass()
				);

				// Show how much damage was actually applied.
				UE_LOG(LogTemp, Warning,
					TEXT("DAMAGE TEST: Applied %f damage to %s"),
					DamageApplied,
					*GetNameSafe(HitResult.GetActor())
				);

				canDamage = false;
			}
		}
	}
	// if no valid hit
	else
	{
		UE_LOG(LogTemp, Log, TEXT("NPCEnemy actor \"%s\" did not detect any valid hit on last attack."), *ownerName);
	}
}

// Sets default values
ANPCEnemy::ANPCEnemy()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void ANPCEnemy::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ANPCEnemy::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void ANPCEnemy::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

