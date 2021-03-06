// Copyright Jeff Brown 2020.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "Particles/ParticleSystemComponent.h"
#include "Components/StaticMeshComponent.h"
#include "PhysicsEngine/RadialForceComponent.h"
#include "Kismet/GameplayStatics.h"
#include "GameFramework/Actor.h"
#include "Projectile.generated.h"

UCLASS()
class BATTLETANK_API AProjectile : public AActor
{
  GENERATED_BODY()

public:
  // Sets default values for this actor's properties
  AProjectile();

  // Launch projectile
  void LaunchProjectile(float Speed);

protected:
  // Called when the game starts or when spawned
  virtual void BeginPlay() override;

private:
  UProjectileMovementComponent *ProjectileMovement = nullptr;

  UPROPERTY(EditDefaultsOnly, Category = "Setup")
  float DestroyDelay = 10; // 10 second default delay to destroy projectile

  UPROPERTY(EditDefaultsOnly, Category = "Setup")
  float ProjectileDamage = 20.f; // Default damage

  UPROPERTY(VisibleAnywhere, Category = "Components")
  UStaticMeshComponent *CollisionMesh = nullptr;

  UPROPERTY(VisibleAnywhere, Category = "Components")
  UParticleSystemComponent *ExplosionBlast = nullptr;

  UPROPERTY(VisibleAnywhere, Category = "Components")
  UParticleSystemComponent *LaunchBlast = nullptr;

  UPROPERTY(VisibleAnywhere, Category = "Components")
  URadialForceComponent *ExplosionForce = nullptr;

  UFUNCTION(BlueprintCallable, Category = "Event")
  void OnHit(UPrimitiveComponent *HitComponent, AActor *OtherActor, UPrimitiveComponent *OtherComponent, FVector NormalImpulse, const FHitResult &Hit);

  void OnTimerExpire();
};
