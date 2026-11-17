// Fill out your copyright notice in the Description page of Project Settings.
#include "MazeGameMode.h"

// Constructor
AMazeGameMode::AMazeGameMode()
{
	// GameMode setup
}

void AMazeGameMode::InitGameState()
{
	Super::InitGameState();
	
	// If there is no ovveride for the default pawn class
	if (DefaultPawnClass == AMazeCharacter::StaticClass())
	{
		// Set default pawn
		DefaultPawnClass = DefaultPlayerCharacter;
	}
}
