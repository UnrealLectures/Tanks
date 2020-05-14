// Copyright Jeff Brown 2020.

#include "TankPlayerController.h"
#include "TankAimingComponent.h"

void ATankPlayerController::BeginPlay()
{
  Super::BeginPlay();
  auto AimingComponent = GetPawn()->FindComponentByClass<UTankAimingComponent>();
  if (!AimingComponent)
  {
    return;
  }
  FoundAimingComponent(AimingComponent);
}

void ATankPlayerController::Tick(float DeltaTime)
{
  Super::Tick(DeltaTime);
  AimTowardsCrosshair();
}

void ATankPlayerController::AimTowardsCrosshair()
{
  if (!GetPawn())
  {
    return;
  }
  // Exit if no tank is controlled
  auto AimingComponent = GetPawn()->FindComponentByClass<UTankAimingComponent>();
  if (!AimingComponent)
  {
    return;
  }

  FVector HitLocation; // Out Parameter

  // If it hits the landscape...
  if (GetSightRayHitLocation(HitLocation)) // Has a "side-effect", is going to line trace
  {
    // Tell controlled tank to aim at this point
    AimingComponent->AimAt(HitLocation);
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