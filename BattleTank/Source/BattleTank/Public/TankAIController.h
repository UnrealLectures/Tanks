// Copyright Jeff Brown 2020.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "TankAIController.generated.h"

// Forward Declarations
class ATank;

UCLASS()
class BATTLETANK_API ATankAIController : public AAIController
{
  GENERATED_BODY()

public:
  virtual void BeginPlay() override;
  virtual void Tick(float DeltaTime) override;

private:
  // How close can AI tank get to player
  float AcceptanceRadius = 3000;
};
