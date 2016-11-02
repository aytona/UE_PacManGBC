// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/Character.h"
#include "PacManCharacter.h"
#include "Enemy.generated.h"

UCLASS()
class PACMANGBC_API AEnemy : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AEnemy();

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	
	// Called every frame

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* InputComponent) override;

    UFUNCTION()
        void OnCollision(UPrimitiveComponent* OverlappedComp,
            AActor* OtherActor,
            UPrimitiveComponent* OtherComp,
            int32 OtherBodyIndex,
            bool bFromSweep,
            const FHitResult& SweepResult);
	
    UPROPERTY(EditDefaultsOnly, Category = Body)
        UStaticMeshComponent* EnemyBody;

    void SetVulnerable();
    void SetInvulnerable();

    void SetMove(bool MoveIt);
    void Kill();
    void ReArm();

    bool bIsDead;

private:
    bool bIsVulnerable;
    FTimerHandle TimerVulnerable;

    class UMaterialInterface* DefaultMaterial;
    class UMaterialInterface* VulnerableMaterial;
};
