// Copyright Jeff Brown 2020.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/NavMovementComponent.h"
#include "TankMovementComponent.generated.h"

//Forward declarations
class UTankTrack;

UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class BATTLETANK_API UTankMovementComponent : public UNavMovementComponent
{
  GENERATED_BODY()

public:
  UFUNCTION(BlueprintCallable, Category = "Input")
  void Initialize(UTankTrack *LeftTrackToSet, UTankTrack *RightTrackToSet);

  UFUNCTION(BlueprintCallable, Category = "Input")
  void IntendMoveForward(float Throw);

  UFUNCTION(BlueprintCallable, Category = "Input")
  void IntendRotate(float Throw);

private:
  UTankTrack *LeftTrack = nullptr;
  UTankTrack *RightTrack = nullptr;

  // Call from pathfinding logic by the AI Controllers
  virtual void RequestDirectMove(const FVector &MoveVelocity, bool bForceMaxSpeed) override;
};
