// Fill out your copyright notice in the Description page of Project Settings.

#include "PacManGBC.h"
#include "Enemy.h"


// Sets default values
AEnemy::AEnemy()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.

    SetActorEnableCollision(true);

    GetCapsuleComponent()->SetCapsuleRadius(40.0f);
    GetCapsuleComponent()->SetCapsuleHalfHeight(50.0f);

    static ConstructorHelpers::FObjectFinder<UStaticMesh>CylinderObj(TEXT("'/Game/StarterContent/Shapes/Shapes_Cylinder'"));

    EnemyBody = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Body"));
    EnemyBody->StaticMesh = CylinderObj.Object;
    EnemyBody->SetRelativeScale3D(FVector(0.7f, 0.7f, 1.0f));
    EnemyBody->AttachTo(RootComponent);

    // Set vulnerable material, same for all enemies
    static ConstructorHelpers::FObjectFinder<UMaterial>VulnerableMat(TEXT("'/Game/Materials/M_Enemy/Vulnerable'"));
    VulnerableMaterial = VulnerableMat.Object;

    //AIControllerClass = AAIEnemy::StaticClass();
}

// Called when the game starts or when spawned
void AEnemy::BeginPlay()
{
	Super::BeginPlay();
	

    DefaultMaterial = EnemyBody->GetMaterial(0);
    GetCapsuleComponent()->OnComponentBeginOverlap.AddDynamic(this, &AEnemy::OnCollision);
}

// Called to bind functionality to input
void AEnemy::SetupPlayerInputComponent(class UInputComponent* InputComponent)
{
	Super::SetupPlayerInputComponent(InputComponent);

}

void AEnemy::OnCollision(UPrimitiveComponent* OverlappedComp,
    AActor* OtherActor,
    UPrimitiveComponent* OtherComp,
    int32 OtherBodyIndex,
    bool bFromSweep,
    const FHitResult& SweepResult) {
    if (OtherActor->IsA(APacManCharacter::StaticClass())) {
        if (bIsVulnerable) {
            Kill();
        } else {
            APacManCharacter* PacMan = Cast<APacManCharacter>(OtherActor);
            PacMan->Kill();
        }
    }
}

void AEnemy::SetVulnerable() {
    GetWorldTimerManager().SetTimer(TimerVulnerable, this, &AEnemy::SetInvulnerable, 10.0f, false);

    if (bIsVulnerable) {
        return;
    }

    bIsVulnerable = true;
    EnemyBody->SetMaterial(0, VulnerableMaterial);
    GetCharacterMovement()->MaxWalkSpeed = 50.0f;
}

void AEnemy::SetInvulnerable() {
    GetWorldTimerManager().ClearTimer(TimerVulnerable);
    bIsVulnerable = false;
    EnemyBody->SetMaterial(0, DefaultMaterial);
    GetCharacterMovement()->MaxWalkSpeed = 150.0f;
}

void AEnemy::SetMove(bool MoveIt) {

}

void AEnemy::Kill() {
    if (bIsDead) {
        return;
    }

    bIsDead = true;
    GetCharacterMovement()->MaxWalkSpeed = 300.0f;
}

void AEnemy::ReArm() {
    bIsDead = false;
    GetCharacterMovement()->MaxWalkSpeed = 150.0f;

    if (bIsVulnerable) {
        SetInvulnerable();
    }
}