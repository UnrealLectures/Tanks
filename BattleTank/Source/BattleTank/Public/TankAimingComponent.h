// Copyright Jeff Brown 2020.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "TankAimingComponent.generated.h"

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

  // TODO Setter for turret reference

public:
  void AimAt(FVector HitLocation, float LaunchSpeed);

private:
  UTankBarrel *Barrel = nullptr;
  void MoveBarrelTowards(FVector AimDirection);
};
