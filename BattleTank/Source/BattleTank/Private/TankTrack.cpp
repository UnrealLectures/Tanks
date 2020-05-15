// Copyright Jeff Brown 2020.

#include "TankTrack.h"

UTankTrack::UTankTrack()
{
  // Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
  // off to improve performance if you don't need them.
  PrimaryComponentTick.bCanEverTick = false;
}

void UTankTrack::BeginPlay()
{
  Super::BeginPlay();
  OnComponentHit.AddDynamic(this, &UTankTrack::OnHit);
}

void UTankTrack::OnHit(UPrimitiveComponent *HitComponent, AActor *OtherActor, UPrimitiveComponent *OtherComponent, FVector NormalImpulse, const FHitResult &Hit)
{
  // Drive the tracks
  DriveTrack();

  // Apply a sideways force
  ApplySidewaysForce();

  // Reset Throttle
  CurrentThrottle = 0;
}

void UTankTrack::SetThrottle(float Throttle)
{
  CurrentThrottle = FMath::Clamp<float>(CurrentThrottle + Throttle, -1.5, 1.5);
}

void UTankTrack::DriveTrack()
{
  auto ForceApplied = GetForwardVector() * CurrentThrottle * TrackMaxDrivingForce;
  auto ForceLocation = GetComponentLocation();
  auto TankRoot = Cast<UPrimitiveComponent>(GetOwner()->GetRootComponent());
  TankRoot->AddForceAtLocation(ForceApplied, ForceLocation);
}

void UTankTrack::ApplySidewaysForce()
{
  // Calculate slippage speed
  auto SlippageSpeed = FVector::DotProduct(GetRightVector(), GetComponentVelocity());

  // Calculate required acceleration to correct this frame
  auto DeltaTime = GetWorld()->GetDeltaSeconds();
  auto CorrectionAcceleration = -SlippageSpeed / DeltaTime * GetRightVector();

  // Get a pointer to the root tank and cast to a mesh component
  auto TankRoot = Cast<UStaticMeshComponent>(GetOwner()->GetRootComponent());

  // Calculate the required force to counteract the slippage, divinding by 2 because 2 tracks (F = (M * A) / 2 )
  auto CorrectionForce = (TankRoot->GetMass() * CorrectionAcceleration) / 2;

  // Apply the correction force
  TankRoot->AddForce(CorrectionForce);
}