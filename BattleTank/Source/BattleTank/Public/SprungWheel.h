// Copyright Jeff Brown 2020.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Components/SphereComponent.h"
#include "PhysicsEngine/PhysicsConstraintComponent.h"
#include "SprungWheel.generated.h"

UCLASS()
class BATTLETANK_API ASprungWheel : public AActor
{
  GENERATED_BODY()

public:
  // Sets default values for this actor's properties
  ASprungWheel();

  // Called every frame
  virtual void Tick(float DeltaTime) override;

protected:
  // Called when the game starts or when spawned
  virtual void BeginPlay() override;

private:
  void SetupConstraint();

  UPROPERTY(VisibleAnywhere, Category = "Components")
  UPhysicsConstraintComponent *MassWheelConstraint = nullptr;

  UPROPERTY(VisibleAnywhere, Category = "Components")
  UPhysicsConstraintComponent *AxleWheelConstraint = nullptr;

  UPROPERTY(VisibleAnywhere, Category = "Components")
  USphereComponent *Wheel = nullptr;

  UPROPERTY(VisibleAnywhere, Category = "Components")
  USphereComponent *Axle = nullptr;
};
