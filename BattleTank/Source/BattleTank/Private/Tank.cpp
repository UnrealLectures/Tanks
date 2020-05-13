// Copyright Jeff Brown 2020.

#include "Tank.h"
#include "TankAimingComponent.h"
#include "TankBarrel.h"
#include "Projectile.h"

// Sets default values
ATank::ATank()
{
  // Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
  PrimaryActorTick.bCanEverTick = false;
}

// Called when the game starts or when spawned
void ATank::BeginPlay()
{
  Super::BeginPlay();
}

void ATank::AimAt(FVector HitLocation)
{
  if (!ensure(TankAimingComponent))
  {
    return;
  }
  TankAimingComponent->AimAt(HitLocation, LaunchSpeed);
}

void ATank::Fire()
{
  bool isReloaded = (FPlatformTime::Seconds() - LastFireTime) > ReloadTimeInSeconds;
  if (Barrel && isReloaded)
  {
    // Spawn a projectile at socket location on barrel
    auto Projectile = GetWorld()->SpawnActor<AProjectile>(
        ProjectileBlueprint,
        Barrel->GetSocketLocation(FName("Projectile")),
        Barrel->GetSocketRotation(FName("Projectile")));

    // Launch Projectile
    Projectile->LaunchProjectile(LaunchSpeed);
    LastFireTime = FPlatformTime::Seconds();
  }
}
