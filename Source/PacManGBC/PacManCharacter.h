// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/Character.h"
#include "PacManGameMode.h"
#include "PacManCharacter.generated.h"

UCLASS()
class PACMANGBC_API APacManCharacter : public ACharacter
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	APacManCharacter();

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	// Called every frame
	virtual void Tick(float DeltaSeconds) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* InputComponent) override;

    void Kill();

private:
	void MoveXAxis(float AxisValue);
	void MoveYAxis(float AxisValue);

	void NewGame();
	void Pause();
	void RestartGame();

	UFUNCTION()
		void OnCollision(UPrimitiveComponent* OverlappedComp,
			AActor* OtherActor,
			UPrimitiveComponent* OtherComp,
			int32 OtherBodyIndex,
			bool bFromSweep,
			const FHitResult& SweepResult);

	FVector CurrentVelocity; // The current Velocity of the player
	APacManGameMode* GameMode;

	uint8 CollectablesToEat;
	uint8 Lives;

	FVector StartPoint;
};
