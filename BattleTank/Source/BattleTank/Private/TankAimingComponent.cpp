// Copyright Jeff Brown 2020.

#include "TankAimingComponent.h"
#include "TankTurret.h"
#include "TankBarrel.h"

#include "Kismet/GameplayStatics.h"

// Sets default values for this component's properties
UTankAimingComponent::UTankAimingComponent()
{
  // Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
  // off to improve performance if you don't need them.
  PrimaryComponentTick.bCanEverTick = false;
}

void UTankAimingComponent::AimAt(FVector HitLocation, float LaunchSpeed)
{
  if (!Barrel)
  {
    return;
  }

  FVector OutLaunchVelocity(0);
  FVector StartLocation = Barrel->GetSocketLocation(FName("Projectile"));

  // Calculate velocity
  bool bHaveAimSolution = UGameplayStatics::SuggestProjectileVelocity(
      this,
      OutLaunchVelocity,
      StartLocation,
      HitLocation,
      LaunchSpeed,
      false,
      0,
      0,
      ESuggestProjVelocityTraceOption::DoNotTrace);

  if (bHaveAimSolution)
  {
    // Turns AimDirection into a unit vector
    auto AimDirection = OutLaunchVelocity.GetSafeNormal();
    MoveBarrelTowards(AimDirection);
    auto Time = GetWorld()->GetTimeSeconds();
    //UE_LOG(LogTemp, Warning, TEXT("%f: Aim Solution Found!"), Time);
  }
  else
  {
    auto Time = GetWorld()->GetTimeSeconds();
    //UE_LOG(LogTemp, Warning, TEXT("%f: NO Aim Solution Found!"), Time);
  }
}

void UTankAimingComponent::SetBarrelReference(UTankBarrel *BarrelToSet)
{
  if (!BarrelToSet)
  {
    return;
  }
  Barrel = BarrelToSet;
}

void UTankAimingComponent::SetTurretReference(UTankTurret *TurretToSet)
{
  if (!TurretToSet)
  {
    return;
  }
  Turret = TurretToSet;
}

void UTankAimingComponent::MoveBarrelTowards(FVector AimDirection)
{
  // If game is paused do not update movement
  if (GetWorld()->IsPaused())
  {
    return;
  }

  // Get diff between current barrel rotation and aim direction
  auto BarrelRotator = Barrel->GetForwardVector().Rotation();
  auto AimAsRotator = AimDirection.Rotation();
  auto DeltaRotator = AimAsRotator - BarrelRotator;

  Barrel->Elevate(DeltaRotator.Pitch);
  Turret->Rotate(DeltaRotator.Yaw);
}
