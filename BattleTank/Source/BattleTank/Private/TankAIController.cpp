// Fill out your copyright notice in the Description page of Project Settings.

#include "TankAIController.h"
#include "TankAimingComponent.h"
#include "Tank.h"

void ATankAIController::Tick(float DeltaSeconds)
{
    Super::Tick(DeltaSeconds);

    auto PlayerTank = GetWorld()->GetFirstPlayerController()->GetPawn();
    auto ControlledTank = GetPawn();

    if (PlayerTank && ControlledTank)
    {
        MoveToActor(PlayerTank, AcceptanceRadius);

        auto AimingComponent = ControlledTank->FindComponentByClass<UTankAimingComponent>();
        AimingComponent->AimAt(PlayerTank->GetActorLocation());

        if (AimingComponent->GetFiringState() == EFiringState::Locked)
        {
            AimingComponent->Fire();
        }
    }
}

void ATankAIController::SetPawn(APawn * InPawn)
{
    Super::SetPawn(InPawn);

    if (InPawn)
    {
        auto PossessedTank = Cast<ATank>(InPawn);
        if (!PossessedTank) return;

        PossessedTank->OnDeath.AddUniqueDynamic(this, &ATankAIController::OnTankDeath);
    }
}

void ATankAIController::OnTankDeath()
{
    if (!GetPawn()) return;
    GetPawn()->DetachFromControllerPendingDestroy();
}


