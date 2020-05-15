// Copyright Jeff Brown 2020.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "TankAIController.generated.h"

UCLASS()
class BATTLETANK_API ATankAIController : public AAIController
{
  GENERATED_BODY()

public:
  virtual void BeginPlay() override;
  virtual void Tick(float DeltaTime) override;

protected:
  // How close can AI tank get to player
  UPROPERTY(EditDefaultsOnly, Category = "Setup")
  float AcceptanceRadius = 7500;

private:
};
