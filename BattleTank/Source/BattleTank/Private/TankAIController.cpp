// Copyright Jeff Brown 2020.

#include "TankAIController.h"

void ATankAIController::BeginPlay()
{
  Super::BeginPlay();

  // Verify and log that AI has successfully possessed a target in scene
  auto ControlledTank = GetControlledTank();
  if (!ControlledTank)
  {
    UE_LOG(LogTemp, Warning, TEXT("AIController not possessing a tank..."));
  }
  else
  {
    UE_LOG(LogTemp, Warning, TEXT("AIController possessing: %s"), *(ControlledTank->GetName()));
  }

  // Verify and log that AI can successfully find player
  auto PlayerTank = GetPlayerTank();
  if (!PlayerTank)
  {
    UE_LOG(LogTemp, Warning, TEXT("AIController can't find player..."));
  }
  else
  {
    UE_LOG(LogTemp, Warning, TEXT("AIController found player: %s"), *(PlayerTank->GetName()));
  }
}

void ATankAIController::Tick(float DeltaTime)
{
  Super::Tick(DeltaTime);

  if (GetPlayerTank())
  {
    // TODO Move towards the player

    // Aim towards the player
    GetControlledTank()->AimAt(GetPlayerTank()->GetActorLocation());

    // TODO Fire if ready
  }
}

ATank *ATankAIController::GetControlledTank() const
{
  return Cast<ATank>(GetPawn());
}

ATank *ATankAIController::GetPlayerTank() const
{
  auto PlayerPawn = GetWorld()->GetFirstPlayerController()->GetPawn();
  if (!PlayerPawn)
  {
    return nullptr;
  }
  return Cast<ATank>(PlayerPawn);
}
