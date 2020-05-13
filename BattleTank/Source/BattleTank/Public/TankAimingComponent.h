// Copyright Jeff Brown 2020.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "TankAimingComponent.generated.h"

// Enumerations
UENUM()
enum class EFiringState : uint8
{
  Reloading,
  Aiming,
  Locked
};

// Forward Declarations
class UTankTurret;
class UTankBarrel;
class AProjectile;

// Holds barrel's properties
UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class BATTLETANK_API UTankAimingComponent : public UActorComponent
{
  GENERATED_BODY()

public:
  // Sets default values for this component's properties
  UTankAimingComponent();

  UFUNCTION(BlueprintCallable, Category = "Input")
  void Initialize(UTankTurret *TurretToSet, UTankBarrel *BarrelToSet);

  UFUNCTION(BlueprintCallable, Category = "Firing")
  void Fire();

  void AimAt(FVector HitLocation);

protected:
  UPROPERTY(BlueprintReadOnly, Category = "State")
  EFiringState FiringState = EFiringState::Aiming;

private:
  void MoveBarrelTowards(FVector AimDirection);

  UTankBarrel *Barrel = nullptr;
  UTankTurret *Turret = nullptr;

  UPROPERTY(EditDefaultsOnly, Category = "Firing")
  float LaunchSpeed = 7500;

  UPROPERTY(EditDefaultsOnly, Category = "Firing")
  float ReloadTimeInSeconds = 3; // Time between shots

  UPROPERTY(EditDefaultsOnly, Category = "Setup")
  TSubclassOf<AProjectile> ProjectileBlueprint;

  double LastFireTime = 0;
};
