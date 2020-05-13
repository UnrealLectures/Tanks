// Copyright Jeff Brown 2020.

#include "TankMovementComponent.h"
#include "TankTrack.h"

void UTankMovementComponent::Initialize(UTankTrack *LeftTrackToSet, UTankTrack *RightTrackToSet)
{
  if (!LeftTrackToSet || !RightTrackToSet)
  {
    return;
  }
  LeftTrack = LeftTrackToSet;
  RightTrack = RightTrackToSet;
}

void UTankMovementComponent::IntendMoveForward(float Throw)
{
  LeftTrack->SetThrottle(Throw);
  RightTrack->SetThrottle(Throw);

  // TODO: Prevent double speed do to dual control use
}