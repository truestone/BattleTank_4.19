// Fill out your copyright notice in the Description page of Project Settings.

#include "Tank.h"
#include "TankBarrel.h"
#include "Projectile.h"
#include "Engine/World.h"

// Sets default values
ATank::ATank()
{
	PrimaryActorTick.bCanEverTick = false;
}

float ATank::TakeDamage(float DamageAmount, FDamageEvent const & DamageEvent, AController * EventInstigator, AActor * DamageCauser)
{
    int32 DamagePoints = FMath::RoundToInt(DamageAmount);
    int32 DamageToApply = FMath::Clamp<int32>(DamagePoints, 0, CurrentHealth);

    CurrentHealth -= DamageToApply;
    if (CurrentHealth <= 0) {
        OnDeath.Broadcast();
    }
    return DamageToApply;
}

float ATank::GetHealthPercent() const
{
    return (float)CurrentHealth / (float)StartingHealth;
}

void ATank::BeginPlay()
{
    Super::BeginPlay();

    CurrentHealth = StartingHealth;
}
