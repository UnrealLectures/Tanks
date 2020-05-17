// Copyright Jeff Brown 2020.

#include "TankAIController.h"
#include "TankAimingComponent.h"
#include "Tank.h"

void ATankAIController::BeginPlay()
{
  Super::BeginPlay();
}

void ATankAIController::Tick(float DeltaTime)
{
  Super::Tick(DeltaTime);

  auto PlayerTank = GetWorld()->GetFirstPlayerController()->GetPawn();
  auto ControlledTank = GetPawn();
  if (!PlayerTank && !ControlledTank)
  {
    return;
  }

  // Move to Player
  MoveToActor(PlayerTank, AcceptanceRadius);

  // Aim towards the player
  auto AimingComponent = ControlledTank->FindComponentByClass<UTankAimingComponent>();
  AimingComponent->AimAt(PlayerTank->GetActorLocation());

  // Fire if locked
  if (AimingComponent->GetFiringState() == EFiringState::Locked)
  {
    AimingComponent->Fire();
  }
}

void ATankAIController::SetPawn(APawn *InPawn)
{
  Super::SetPawn(InPawn);
  if (InPawn)
  {
    auto PossessedTank = Cast<ATank>(InPawn);
    if (!PossessedTank)
    {
      return;
    }
    PossessedTank->OnDeath.AddUniqueDynamic(this, &ATankAIController::OnPossessedTankDeath);
  }
}

void ATankAIController::OnPossessedTankDeath()
{
  UE_LOG(LogTemp, Warning, TEXT("Received"));
}