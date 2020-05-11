// Copyright Jeff Brown 2020.

#include "TankAimingComponent.h"
#include "TankBarrel.h"

// Sets default values for this component's properties
UTankAimingComponent::UTankAimingComponent()
{
  // Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
  // off to improve performance if you don't need them.
  PrimaryComponentTick.bCanEverTick = true;
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
      ESuggestProjVelocityTraceOption::DoNotTrace);

  if (bHaveAimSolution)
  {
    // Turns AimDirection into a unit vector
    auto AimDirection = OutLaunchVelocity.GetSafeNormal();
    MoveBarrelTowards(AimDirection);
  }
  else
  {
  }
}

void UTankAimingComponent::SetBarrelReference(UTankBarrel *BarrelToSet)
{
  Barrel = BarrelToSet;
}

void UTankAimingComponent::MoveBarrelTowards(FVector AimDirection)
{
  // Get diff between current barrel rotation and aim direction
  auto BarrelRotator = Barrel->GetForwardVector().Rotation();
  auto AimAsRotator = AimDirection.Rotation();
  auto DeltaRotator = AimAsRotator - BarrelRotator;

  Barrel->Elevate(5);
}
