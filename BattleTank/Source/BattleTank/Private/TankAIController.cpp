// Copyright Jeff Brown 2020.

#include "TankAIController.h"
#include "Tank.h"

void ATankAIController::BeginPlay()
{
  Super::BeginPlay();
}

void ATankAIController::Tick(float DeltaTime)
{
  Super::Tick(DeltaTime);

  auto PlayerTank = Cast<ATank>(GetWorld()->GetFirstPlayerController()->GetPawn());
  auto ControlledTank = Cast<ATank>(GetPawn());
  if (PlayerTank && ControlledTank)
  {
    // TODO Move towards the player

    // Aim towards the player
    ControlledTank->AimAt(PlayerTank->GetActorLocation());

    // Fire
    ControlledTank->Fire(); // TODO limit firing rate
  }
}
