// Copyright Jeff Brown 2020.

#include "TankAimingComponent.h"
#include "TankTurret.h"
#include "TankBarrel.h"
#include "Projectile.h"

#include "Kismet/GameplayStatics.h"

// Sets default values for this component's properties
UTankAimingComponent::UTankAimingComponent()
{
  // Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
  // off to improve performance if you don't need them.
  PrimaryComponentTick.bCanEverTick = true;
}

void UTankAimingComponent::BeginPlay()
{
  Super::BeginPlay();

  LastFireTime = FPlatformTime::Seconds();
}

void UTankAimingComponent::TickComponent(float DeltaTime, enum ELevelTick TickType, FActorComponentTickFunction *ThisTickFunction)
{
  Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

  if ((FPlatformTime::Seconds() - LastFireTime) < ReloadTimeInSeconds)
  {
    FiringState = EFiringState::Reloading;
  }
  else if (IsBarrelMoving())
  {
    FiringState = EFiringState::Aiming;
  }
  else
  {
    FiringState = EFiringState::Locked;
  }
}

void UTankAimingComponent::AimAt(FVector HitLocation)
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
    AimDirection = OutLaunchVelocity.GetSafeNormal();
    MoveBarrelTowards(AimDirection);
  }
}

void UTankAimingComponent::Initialize(UTankTurret *TurretToSet, UTankBarrel *BarrelToSet)
{
  Turret = TurretToSet;
  Barrel = BarrelToSet;
}

void UTankAimingComponent::MoveBarrelTowards(FVector IntendAimDirection)
{
  // If game is paused do not update movement
  // If barrel or turret isn't set do not update movement
  if (GetWorld()->IsPaused() || !Barrel || !Turret)
  {
    return;
  }

  // Get diff between current barrel rotation and aim direction
  auto BarrelRotator = Barrel->GetForwardVector().Rotation();
  auto AimAsRotator = IntendAimDirection.Rotation();
  auto DeltaRotator = AimAsRotator - BarrelRotator;

  Barrel->Elevate(DeltaRotator.Pitch);
  Turret->Rotate(DeltaRotator.Yaw);
}

bool UTankAimingComponent::IsBarrelMoving()
{
  if (!ensure(Barrel))
  {
    return false;
  }

  auto BarrelForward = Barrel->GetForwardVector();
  return !BarrelForward.Equals(AimDirection, 0.01);
}

void UTankAimingComponent::Fire()
{

  if (FiringState != EFiringState::Reloading)
  {
    if (!(Barrel && ProjectileBlueprint) || GetWorld()->IsPaused())
    {
      return;
    }
    // Spawn a projectile at socket location on barrel
    auto Projectile = GetWorld()->SpawnActor<AProjectile>(
        ProjectileBlueprint,
        Barrel->GetSocketLocation(FName("Projectile")),
        Barrel->GetSocketRotation(FName("Projectile")));

    // Launch Projectile
    Projectile->LaunchProjectile(LaunchSpeed); // TODO Uncomment this
    LastFireTime = FPlatformTime::Seconds();
  }
}