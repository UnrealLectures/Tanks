// Copyright Jeff Brown 2020.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "Tank.generated.h"

// Forward Declarations
class UTankAimingComponent;
class UTankTurret;
class UTankBarrel;
class AProjectile;

UCLASS()
class BATTLETANK_API ATank : public APawn
{
  GENERATED_BODY()

public:
  // Sets default values for this pawn's properties
  ATank();

  UFUNCTION(BlueprintCallable, Category = Firing)
  void Fire();

  void AimAt(FVector HitLocation);

protected:
  // Called when the game starts or when spawned
  virtual void BeginPlay() override;

  UPROPERTY(BlueprintReadOnly)
  UTankAimingComponent *TankAimingComponent = nullptr;

private:
  UPROPERTY(EditDefaultsOnly, Category = "Firing")
  float LaunchSpeed = 7500;

  UPROPERTY(EditDefaultsOnly, Category = "Firing")
  float ReloadTimeInSeconds = 3; // Time between shots

  UPROPERTY(EditDefaultsOnly, Category = "Setup")
  TSubclassOf<AProjectile> ProjectileBlueprint;

  // Add a local barrel reference for spawning projectile
  UTankBarrel *Barrel = nullptr; // TODO remove

  double LastFireTime = 0;
};
