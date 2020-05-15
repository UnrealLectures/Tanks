// Copyright Jeff Brown 2020.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "Particles/ParticleSystemComponent.h"
#include "Components/StaticMeshComponent.h"
//#include "Components/PrimitiveComponent.h"
#include "GameFramework/Actor.h"
#include "Projectile.generated.h"

UCLASS()
class BATTLETANK_API AProjectile : public AActor
{
  GENERATED_BODY()

public:
  // Sets default values for this actor's properties
  AProjectile();

  // Called every frame
  virtual void Tick(float DeltaTime) override;

  // Launch projectile
  void LaunchProjectile(float Speed);

protected:
  // Called when the game starts or when spawned
  virtual void BeginPlay() override;

private:
  UProjectileMovementComponent *ProjectileMovement = nullptr;

  UPROPERTY(VisibleANywhere, Category = "Components")
  UStaticMeshComponent *CollisionMesh = nullptr;

  UPROPERTY(VisibleANywhere, Category = "Components")
  UParticleSystemComponent *LaunchBlast = nullptr;
};
