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

// Holds barrel's properties
UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class BATTLETANK_API UTankAimingComponent : public UActorComponent
{
  GENERATED_BODY()

public:
  // Sets default values for this component's properties
  UTankAimingComponent();

  // Setter for barrel component
  void SetBarrelReference(UTankBarrel *BarrelToSet);

  // Setter for turret component
  void SetTurretReference(UTankTurret *TurretToSet);

  void AimAt(FVector HitLocation, float LaunchSpeed);

protected:
  UPROPERTY(BlueprintReadOnly, Category = "State")
  EFiringState FiringState = EFiringState::Reloading;

private:
  UTankBarrel *Barrel = nullptr;
  UTankTurret *Turret = nullptr;

  void MoveBarrelTowards(FVector AimDirection);
};
