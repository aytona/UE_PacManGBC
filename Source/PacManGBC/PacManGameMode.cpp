// Fill out your copyright notice in the Description page of Project Settings.

#include "PacManGBC.h"
#include "PacManGameMode.h"

EGameState APacManGameMode::GetCurrentState() const
{
	return CurrentState;
}

void APacManGameMode::SetCurrentState(EGameState value)
{
	CurrentState = value;
}
