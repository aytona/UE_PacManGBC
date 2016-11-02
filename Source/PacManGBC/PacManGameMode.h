// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/GameMode.h"
#include "PacManGameMode.generated.h"

enum class EGameState : short
{
	EMenu,
	EPlaying,
	EPause,
	EWin,
	EGameOver
};

UCLASS()
class PACMANGBC_API APacManGameMode : public AGameMode
{
	GENERATED_BODY()
	
public:
	EGameState GetCurrentState() const;
	void SetCurrentState(EGameState value);

private:
	EGameState CurrentState;
};
