// Copyright Jeff Brown 2020.

#include "TankAIController.h"
#include "TankAimingComponent.h"

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
