// Copyright Jeff Brown 2020.

#include "TankMovementComponent.h"
#include "TankTrack.h"

void UTankMovementComponent::Initialize(UTankTrack *LeftTrackToSet, UTankTrack *RightTrackToSet)
{
  LeftTrack = LeftTrackToSet;
  RightTrack = RightTrackToSet;
}

void UTankMovementComponent::RequestDirectMove(const FVector &MoveVelocity, bool bForceMaxSpeed)
{
  // No need to call super, replacing functionality

  auto TankForward = GetOwner()->GetActorForwardVector().GetSafeNormal();
  auto AIForwardIntention = MoveVelocity.GetSafeNormal();

  auto ForwardThrow = FVector::DotProduct(TankForward, AIForwardIntention);
  IntendMoveForward(ForwardThrow); // TODO uncomment this

  auto RightThrow = FVector::CrossProduct(TankForward, AIForwardIntention).Z;
  IntendRotate(RightThrow);
}

void UTankMovementComponent::IntendMoveForward(float Throw)
{
  if (!LeftTrack || !RightTrack)
  {
    return;
  }
  LeftTrack->SetThrottle(Throw);
  RightTrack->SetThrottle(Throw);
}

void UTankMovementComponent::IntendRotate(float Throw)
{
  if (!LeftTrack || !RightTrack)
  {
    return;
  }
  LeftTrack->SetThrottle(Throw);
  RightTrack->SetThrottle(-Throw);
}