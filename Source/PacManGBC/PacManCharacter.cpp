// Fill out your copyright notice in the Description page of Project Settings.

#include "PacManGBC.h"
#include "PacManCharacter.h"

#include "Collectable.h"


// Sets default values
APacManCharacter::APacManCharacter()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void APacManCharacter::BeginPlay()
{
	Super::BeginPlay();
	
	SetActorEnableCollision(true);
	GetCapsuleComponent()->OnComponentBeginOverlap.AddDynamic(this, &APacManCharacter::OnCollision);

	GameMode = Cast<APacManGameMode>(UGameplayStatics::GetGameMode(this));

	for (TActorIterator<ACollectable> CollectableItr(GetWorld()); CollectableItr; ++CollectableItr)
	{
		++CollectablesToEat;
	}

	StartPoint = GetActorLocation();
	Lives = 3;
}

// Called every frame
void APacManCharacter::Tick( float DeltaTime )
{
	Super::Tick( DeltaTime );

}


// Called to bind functionality to input
void APacManCharacter::SetupPlayerInputComponent(class UInputComponent* InputComponent)
{
	Super::SetupPlayerInputComponent(InputComponent);

	InputComponent->BindAxis("MoveX", this, &APacManCharacter::MoveXAxis);
	InputComponent->BindAxis("MoveY", this, &APacManCharacter::MoveYAxis);

	InputComponent->BindAction("NewGame", IE_Pressed, this, &APacManCharacter::NewGame);
	InputComponent->BindAction("Pause", IE_Pressed, this, &APacManCharacter::Pause);
	InputComponent->BindAction("Restart", IE_Pressed, this, &APacManCharacter::RestartGame);

}

void APacManCharacter::MoveXAxis(float AxisValue)
{
	CurrentVelocity.X = AxisValue;
	AddMovementInput(CurrentVelocity);
}

void APacManCharacter::MoveYAxis(float AxisValue)
{
	CurrentVelocity.Y = AxisValue;
	AddMovementInput(CurrentVelocity);
}

void APacManCharacter::NewGame()
{
	if (GameMode->GetCurrentState() == EGameState::EMenu)
	{
		GameMode->SetCurrentState(EGameState::EPlaying);
	}
}

void APacManCharacter::Pause()
{
	if (GameMode->GetCurrentState() == EGameState::EPlaying)
	{
		GameMode->SetCurrentState(EGameState::EPause);
	}
	else if (GameMode->GetCurrentState() == EGameState::EPause)
	{
		GameMode->SetCurrentState(EGameState::EPlaying);
	}
}

void APacManCharacter::RestartGame()
{
	GetWorld()->GetFirstPlayerController()->ConsoleCommand(TEXT("RestartLevel"));
}

void APacManCharacter::Kill()
{
	if (--Lives == 0)
	{
		GameMode->SetCurrentState(EGameState::EGameOver);
	}
	else
	{
		SetActorLocation(StartPoint);
	}
}

void APacManCharacter::OnCollision(UPrimitiveComponent * OverlappedComp, AActor * OtherActor, UPrimitiveComponent * OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult & SweepResult)
{
	if (GameMode->GetCurrentState() == EGameState::EPlaying)
	{
		if (OtherActor->IsA(ACollectable::StaticClass()))
		{
			OtherActor->Destroy();

			if (--CollectablesToEat == 0)
			{
				GameMode->SetCurrentState(EGameState::EWin);
			}
		}
	}
}
