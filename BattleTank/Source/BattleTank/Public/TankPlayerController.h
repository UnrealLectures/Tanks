// Copyright Jeff Brown 2020.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "TankPlayerController.generated.h"

// Forward Declarations
class ATank;

UCLASS()
class BATTLETANK_API ATankPlayerController : public APlayerController
{
  GENERATED_BODY()

public:
  virtual void BeginPlay() override;
  virtual void Tick(float DeltaTime) override;

protected:
  UFUNCTION(BlueprintCallable, Category = "Setup")
  ATank *GetControlledTank() const;

private:
  // Start tank moving barrel so that a shot will hit where the crosshair intersects the world
  void AimTowardsCrosshair();

  // Return an OUT parameter, true if hit landscape
  bool GetSightRayHitLocation(FVector &HitLocation) const;

  // Get the world position you are looking at based on screen location of an aiming parameter
  bool GetLookDirection(FVector2D ScreenLocation, FVector &LookDirection) const;

  // Set hit location out parameter
  bool GetLookVectorHitLocation(FVector LookDirection, FVector &HitLocation) const;

  UPROPERTY(EditDefaultsOnly)
  float CrosshairXLocation = 0.5;
  UPROPERTY(EditDefaultsOnly)
  float CrosshairYLocation = 0.3;
  UPROPERTY(EditDefaultsOnly)
  float LineTraceRange = 1000000; // 10 kilometers
};
