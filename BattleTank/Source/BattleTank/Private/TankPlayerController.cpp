// Copyright Jeff Brown 2020.

#include "TankPlayerController.h"
#include "Tank.h"

void ATankPlayerController::BeginPlay()
{
  Super::BeginPlay();
}

void ATankPlayerController::Tick(float DeltaTime)
{
  Super::Tick(DeltaTime);
  AimTowardsCrosshair();
}

ATank *ATankPlayerController::GetControlledTank() const
{
  return Cast<ATank>(GetPawn());
}

void ATankPlayerController::AimTowardsCrosshair()
{
  // Exit if no tank is controlled
  if (!GetControlledTank())
  {
    return;
  }

  FVector HitLocation; // Out Parameter

  // If it hits the landscape...
  if (GetSightRayHitLocation(HitLocation)) // Has a "side-effect", is going to line trace
  {
    // TODO: Tell controlled tank to aim at this point
    GetControlledTank()->AimAt(HitLocation);
  }
}

// Get world location if linetrace through crosshair, true if hits landscape
bool ATankPlayerController::GetSightRayHitLocation(FVector &HitLocation) const
{
  /// Find the crosshair position
  int32 ViewportSizeX, ViewportSizeY;
  GetViewportSize(ViewportSizeX, ViewportSizeY);
  auto ScreenLocation = FVector2D(ViewportSizeX * CrosshairXLocation, ViewportSizeY * CrosshairYLocation);

  // "De-project" the screen position fo the crosshair to a world direction
  FVector LookDirection;
  if (GetLookDirection(ScreenLocation, LookDirection))
  {
    // Line Trace along that LookDirection and see what we hit (to a max range)
    GetLookVectorHitLocation(LookDirection, HitLocation);
  }
  return true;
}

bool ATankPlayerController::GetLookDirection(FVector2D ScreenLocation, FVector &LookDirection) const
{
  FVector CameraWorldLocation;
  return DeprojectScreenPositionToWorld(ScreenLocation.X, ScreenLocation.Y, CameraWorldLocation, LookDirection);
}

bool ATankPlayerController::GetLookVectorHitLocation(FVector LookDirection, FVector &HitLocation) const
{
  FHitResult HitResult;

  // Get start / end point of raytrace
  auto StartLocation = PlayerCameraManager->GetCameraLocation();
  auto EndLocation = StartLocation + LookDirection * LineTraceRange;

  if (GetWorld()->LineTraceSingleByChannel(
          HitResult,
          StartLocation,
          EndLocation,
          ECollisionChannel::ECC_Visibility))
  {
    HitLocation = HitResult.Location;
    return true;
  }
  HitLocation = FVector(0);
  return false;
}