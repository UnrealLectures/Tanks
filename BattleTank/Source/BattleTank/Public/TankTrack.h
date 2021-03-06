// Copyright Jeff Brown 2020.

#pragma once

#include "CoreMinimal.h"
#include "Components/StaticMeshComponent.h"
#include "TankTrack.generated.h"

UCLASS(meta = (BlueprintSpawnableComponent))
class BATTLETANK_API UTankTrack : public UStaticMeshComponent
{
  GENERATED_BODY()

public:
  UTankTrack();

  // Set throttle between -1 and +1
  UFUNCTION(BlueprintCallable, Category = "Input")
  void SetThrottle(float Throttle);

  // Max force per track, in Newtons
  UPROPERTY(EditDefaultsOnly, Category = "Input")
  float TrackMaxDrivingForce = 40000000; // Assume 40 ton tank, 1g accel, units are CM

private:
  void DriveTrack(float CurrentThrottle);

  TArray<class ASprungWheel *> GetWheels() const;
};
