// Copyright Jeff Brown 2020.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "Tank.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FTankDelegate);

UCLASS()
class BATTLETANK_API ATank : public APawn
{
  GENERATED_BODY()

public:
  // Sets default values for this pawn's properties
  ATank();

  // Called by engine when actor damage is dealt
  virtual float TakeDamage(float DamageAmount, struct FDamageEvent const &DamageEvent, class AController *EventInstigator, AActor *DamageCauser) override;

  // Returns current health as a percentage of starting health between 0 and 1
  UFUNCTION(BlueprintPure, Category = "Health")
  float GetHealthPercent() const;

  FTankDelegate OnDeath;

protected:
  // Called when the game starts or when spawned
  virtual void BeginPlay() override;

private:
  UPROPERTY(EditDefaultsOnly, Category = "Setup")
  int32 StartingHealth = 100;

  UPROPERTY(VisibleAnywhere, Category = "Health")
  int32 CurrentHealth; // Init in begin play
};
