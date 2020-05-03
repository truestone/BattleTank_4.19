// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "Tank.generated.h"

class UTankBarrel;
class UTankTurret;
class UTankAimingComponent;
class AProjectile;

UCLASS()
class BATTLETANK_API ATank : public APawn
{
    GENERATED_BODY()

public:
    void AimAt(FVector HitLocation);

    UFUNCTION(BlueprintCallable, Category = Firing)
    void Fire();

    UFUNCTION(BlueprintCallable, Category = Setup)
    void SetBarrelReference(UTankBarrel* BarrelToSet);

    UFUNCTION(BlueprintCallable, Category = Setup)
    void SetTurretReference(UTankTurret* TurretToSet);

protected:
    UTankAimingComponent* TankAimingComponent = nullptr;

private:
	ATank();

	virtual void BeginPlay() override;

    virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
    
    UPROPERTY(EditDefaultsOnly, Category = Firing)
    float LaunchSpeed = 4000;  // 1000 m/s

    UPROPERTY(EditDefaultsOnly, Category = Setup)
    TSubclassOf<AProjectile> ProjectileBlueprint;

    UTankBarrel* Barrel = nullptr;

    UPROPERTY(EditDefaultsOnly, Category = Firing)
    float ReloadTimeInSeconds = 3;

    double LastFireTime = 0;
};
