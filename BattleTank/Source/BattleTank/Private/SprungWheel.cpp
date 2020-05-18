// Copyright Jeff Brown 2020.

#include "SprungWheel.h"

// Sets default values
ASprungWheel::ASprungWheel()
{
  // Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
  PrimaryActorTick.bCanEverTick = true;
  PrimaryActorTick.TickGroup = TG_PostPhysics;

  MassWheelConstraint = CreateDefaultSubobject<UPhysicsConstraintComponent>(FName("MassWheelConstraint"));
  SetRootComponent(MassWheelConstraint);

  Axle = CreateDefaultSubobject<USphereComponent>(FName("Axle"));
  Axle->SetupAttachment(MassWheelConstraint); // Slightly better than attachtocomponent, works only in constructor

  Wheel = CreateDefaultSubobject<USphereComponent>(FName("Wheel"));
  Wheel->SetupAttachment(Axle); // Slightly better than attachtocomponent, works only in constructor

  AxleWheelConstraint = CreateDefaultSubobject<UPhysicsConstraintComponent>(FName("AxleWheelConstraint"));
  AxleWheelConstraint->SetupAttachment(Axle); // Slightly better than attachtocomponent, works only in constructor
}

// Called when the game starts or when spawned
void ASprungWheel::BeginPlay()
{
  Super::BeginPlay();

  Wheel->SetNotifyRigidBodyCollision(true);
  Wheel->OnComponentHit.AddDynamic(this, &ASprungWheel::OnHit);

  SetupConstraint();
}

// Called every frame
void ASprungWheel::Tick(float DeltaTime)
{
  Super::Tick(DeltaTime);

  if (GetWorld()->TickGroup == TG_PostPhysics)
  {
    TotalForceMagnitudeThisFrame = 0; // reset after applying force
  }
}

void ASprungWheel::SetupConstraint()
{
  if (!GetAttachParentActor())
  {
    return;
  }
  UPrimitiveComponent *BodyRoot = Cast<UPrimitiveComponent>(GetAttachParentActor()->GetRootComponent());
  if (!BodyRoot)
  {
    return;
  }
  MassWheelConstraint->SetConstrainedComponents(BodyRoot, NAME_None, Axle, NAME_None);
  AxleWheelConstraint->SetConstrainedComponents(Axle, NAME_None, Wheel, NAME_None);
}

void ASprungWheel::AddDrivingForce(float ForceMagnitude)
{
  TotalForceMagnitudeThisFrame += ForceMagnitude;
}

void ASprungWheel::OnHit(UPrimitiveComponent *HitComponent, AActor *OtherActor, UPrimitiveComponent *OtherComp, FVector NormalImpulse, const FHitResult &Hit)
{
  ApplyForce();
}

void ASprungWheel::ApplyForce()
{
  Wheel->AddForce(Axle->GetForwardVector() * TotalForceMagnitudeThisFrame);
}