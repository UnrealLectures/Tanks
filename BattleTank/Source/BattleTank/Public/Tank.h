// Copyright Jeff Brown 2020.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "Tank.generated.h"

// Forward Declarations
class UTankAimingComponent;
class UTankTurret;
class UTankBarrel;

UCLASS()
class BATTLETANK_API ATank : public APawn
{
  GENERATED_BODY()

public:
  // Sets default values for this pawn's properties
  ATank();

  UFUNCTION(BlueprintCallable, Category = Setup)
  void SetBarrelReference(UTankBarrel *BarrelToSet);

  UFUNCTION(BlueprintCallable, Category = Setup)
  void SetTurretReference(UTankTurret *TurretToSet);

  // Called to bind functionality to input
  virtual void SetupPlayerInputComponent(class UInputComponent *PlayerInputComponent) override;

  void AimAt(FVector HitLocation);

protected:
  // Called when the game starts or when spawned
  virtual void BeginPlay() override;

  UTankAimingComponent *TankAimingComponent = nullptr;

private:
  UPROPERTY(EditAnywhere, Category = Firing)
  float LaunchSpeed = 10000;
};
