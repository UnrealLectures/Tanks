// Copyright Jeff Brown 2020.

#include "Projectile.h"

// Sets default values
AProjectile::AProjectile()
{
  // Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
  PrimaryActorTick.bCanEverTick = false;

  CollisionMesh = CreateDefaultSubobject<UStaticMeshComponent>(FName("Collision Mesh"));
  SetRootComponent(CollisionMesh);
  CollisionMesh->SetNotifyRigidBodyCollision(true); // Same as checking Generate hit Events on the collision in BP
  CollisionMesh->SetRelativeScale3D(0.2 * FVector(1.f, 1.f, 1.f));

  ExplosionBlast = CreateDefaultSubobject<UParticleSystemComponent>(FName("Explosion Blast"));
  ExplosionBlast->AttachToComponent(RootComponent, FAttachmentTransformRules::KeepRelativeTransform);
  ExplosionBlast->bAutoActivate = false;
  ExplosionBlast->SetRelativeScale3D(5 * FVector(1.f, 1.f, 1.f));

  LaunchBlast = CreateDefaultSubobject<UParticleSystemComponent>(FName("Launch Blast"));
  LaunchBlast->AttachToComponent(RootComponent, FAttachmentTransformRules::KeepRelativeTransform);
  LaunchBlast->SetRelativeScale3D(5 * FVector(1.f, 1.f, 1.f));

  ExplosionForce = CreateDefaultSubobject<URadialForceComponent>(FName("Explosion Force"));
  ExplosionForce->AttachToComponent(RootComponent, FAttachmentTransformRules::KeepRelativeTransform);

  ProjectileMovement = CreateDefaultSubobject<UProjectileMovementComponent>(FName("Projectile Movement"));
  ProjectileMovement->bAutoActivate = false;
}

// Called when the game starts or when spawned
void AProjectile::BeginPlay()
{
  Super::BeginPlay();
  CollisionMesh->OnComponentHit.AddDynamic(this, &AProjectile::OnHit);
}

void AProjectile::LaunchProjectile(float Speed)
{
  ProjectileMovement->SetVelocityInLocalSpace(FVector::ForwardVector * Speed);
  ProjectileMovement->Activate();
}

void AProjectile::OnHit(UPrimitiveComponent *HitComponent, AActor *OtherActor, UPrimitiveComponent *OtherComponent, FVector NormalImpulse, const FHitResult &Hit)
{
  // Turn off smoke, execute explosion, apply force
  LaunchBlast->Deactivate();
  ExplosionBlast->Activate();
  ExplosionForce->FireImpulse();

  // Remove projectile from world
  SetRootComponent(ExplosionBlast);
  CollisionMesh->DestroyComponent();

  FTimerHandle Timer;
  GetWorld()->GetTimerManager().SetTimer(Timer, this, &AProjectile::OnTimerExpire, DestroyDelay, false);
}

void AProjectile::OnTimerExpire()
{
  Destroy();
}
