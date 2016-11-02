// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/Actor.h"
#include "Collectable.generated.h"

UCLASS()
class PACMANGBC_API ACollectable : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ACollectable();

	UPROPERTY(EditDefaultsOnly, Category = Collectable)
		USphereComponent* BaseCollisionComponent;

	UPROPERTY(EditDefaultsOnly, Category = Collectable)
		UStaticMeshComponent* CollectableMesh;

	UPROPERTY(EditDefaultsOnly, Category = Collectable)
		bool bIsSuperCollectable;
};
