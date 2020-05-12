// Copyright Jeff Brown 2020.

#pragma once

#include "CoreMinimal.h"
#include "Components/StaticMeshComponent.h"
#include "TankTurret.generated.h"

/**
 * 
 */
UCLASS(meta = (BlueprintSpawnableComponent))
class BATTLETANK_API UTankTurret : public UStaticMeshComponent
{
  GENERATED_BODY()

public:
  // -1 is max downward speed +1 is max upward speed
  void Rotate(float RelativeSpeed);

private:
  UPROPERTY(EditDefaultsOnly, Category = Setup)
  float MaxDegreesPerSecond = 25;
};
