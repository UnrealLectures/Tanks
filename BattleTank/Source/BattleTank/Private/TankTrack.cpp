// Copyright Jeff Brown 2020.

#include "TankTrack.h"
#include "SprungWheel.h"
#include "SpawnPoint.h"

UTankTrack::UTankTrack()
{
  // Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
  // off to improve performance if you don't need them.
  PrimaryComponentTick.bCanEverTick = false;
}

void UTankTrack::SetThrottle(float Throttle)
{
  float CurrentThrottleToTrack = FMath::Clamp<float>(Throttle, -1.5, 1.5);
  DriveTrack(CurrentThrottleToTrack);
}

void UTankTrack::DriveTrack(float CurrentThrottle)
{
  auto ForceApplied = CurrentThrottle * TrackMaxDrivingForce;
  auto Wheels = GetWheels();
  auto ForcePerWheel = ForceApplied / Wheels.Num(); // Force as a function of each wheel
  for (ASprungWheel *Wheel : Wheels)                // Iterate through all the wheels in the array of wheels
  {
    Wheel->AddDrivingForce(ForcePerWheel);
  }
}

TArray<ASprungWheel *> UTankTrack::GetWheels() const
{
  TArray<ASprungWheel *> ResultArray;
  TArray<USceneComponent *> Children;
  GetChildrenComponents(true, Children);
  for (USceneComponent *Child : Children)
  {
    auto SpawnPointChild = Cast<USpawnPoint>(Child);
    if (!SpawnPointChild)
    {
      continue;
    }

    AActor *SpawnedChild = SpawnPointChild->GetSpawnedActor();
    auto SprungWheel = Cast<ASprungWheel>(SpawnedChild);
    if (!SprungWheel)
    {
      continue;
    }

    ResultArray.Add(SprungWheel);
  }

  return ResultArray;
}