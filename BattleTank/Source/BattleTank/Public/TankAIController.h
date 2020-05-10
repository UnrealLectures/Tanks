// Copyright Jeff Brown 2020.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"

#include "Tank.h"

#include "TankAIController.generated.h"

/**
 * 
 */
UCLASS()
class BATTLETANK_API ATankAIController : public AAIController
{
  GENERATED_BODY()

public:
  virtual void BeginPlay() override;
  virtual void Tick(float DeltaTime) override;

private:
  ATank *GetControlledTank() const;
  ATank *GetPlayerTank() const;
};
