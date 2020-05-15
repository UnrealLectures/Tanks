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
  Locked,
  OutOfAmmo
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

  virtual void BeginPlay() override;

  virtual void TickComponent(float DeltaTime, enum ELevelTick TickType, FActorComponentTickFunction *ThisTickFunction) override;

  UFUNCTION(BlueprintCallable, Category = "Input")
  void Initialize(UTankTurret *TurretToSet, UTankBarrel *BarrelToSet);

  EFiringState GetFiringState();

  UFUNCTION(BlueprintCallable, Category = "Firing")
  int32 GetRoundsLeft() const;

  UFUNCTION(BlueprintCallable, Category = "Firing")
  void Fire();

  void AimAt(FVector HitLocation);

protected:
  UPROPERTY(BlueprintReadOnly, Category = "State")
  EFiringState FiringState = EFiringState::Reloading;

private:
  void MoveBarrelTowards(FVector IntendAimDirection);
  bool IsBarrelMoving();

  UTankBarrel *Barrel = nullptr;
  UTankTurret *Turret = nullptr;

  UPROPERTY(EditDefaultsOnly, Category = "Firing")
  float LaunchSpeed = 7500;

  UPROPERTY(EditDefaultsOnly, Category = "Firing")
  float ReloadTimeInSeconds = 3; // Time between shots

  UPROPERTY(EditDefaultsOnly, Category = "Firing")
  int32 RoundsLeft = 3;

  UPROPERTY(EditDefaultsOnly, Category = "Setup")
  TSubclassOf<AProjectile> ProjectileBlueprint;

  double LastFireTime = 0;
  FVector AimDirection;
};
