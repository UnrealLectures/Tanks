// Copyright Jeff Brown 2020.

#include "TankTurret.h"

void UTankTurret::Rotate(float RelativeSpeed)
{
  RelativeSpeed = FMath::Clamp<float>(RelativeSpeed, -1, 1);
  auto RotationChange = RelativeSpeed * MaxDegreesPerSecond * GetWorld()->DeltaTimeSeconds;
  auto Rotation = GetRelativeRotation().Yaw + RotationChange;
  SetRelativeRotation(FRotator(0, Rotation, 0));
}