// Fill out your copyright notice in the Description page of Project Settings.

#include "Tank.h"
#include "TankAimingComponent.h"
#include "TankMovementComponent.h"
#include "TankBarrel.h"
#include "Projectile.h"
#include "Engine/World.h"

// Sets default values
ATank::ATank()
{
	PrimaryActorTick.bCanEverTick = false;
}

void ATank::AimAt(FVector HitLocation)
{
    if (!TankAimingComponent) {
        return;
    }
    TankAimingComponent->AimAt(HitLocation, LaunchSpeed);
}

void ATank::Fire()
{
    bool isReloaded = (FPlatformTime::Seconds() - LastFireTime) > ReloadTimeInSeconds;

    if (Barrel && isReloaded)
    {
        auto Projectile = GetWorld()->SpawnActor<AProjectile>(
            ProjectileBlueprint,
            Barrel->GetSocketLocation(FName("Projectile")),
            Barrel->GetSocketRotation(FName("Proejctile")));

        if (!Projectile) {
            UE_LOG(LogTemp, Error, TEXT("Projectile Blueprint is None!"));
            return;
        }

        Projectile->LaunchProjectile(LaunchSpeed);
        LastFireTime = FPlatformTime::Seconds();
    }
}
