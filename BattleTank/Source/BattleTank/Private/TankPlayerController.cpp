// Fill out your copyright notice in the Description page of Project Settings.

#include "TankPlayerController.h"
#include "TankAimingComponent.h"
#include "Tank.h"

void ATankPlayerController::BeginPlay()
{
	Super::BeginPlay();

    auto AimingComponent = GetPawn()->FindComponentByClass<UTankAimingComponent>();
    if (AimingComponent)
    {
        FoundAimingComponent(AimingComponent);
    }
    else
    {
        UE_LOG(LogTemp, Warning, TEXT("Player controller can't find aiming component at Begin Play"));
    }
}

void ATankPlayerController::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);

    AimTowardsCrosshair();
}

void ATankPlayerController::AimTowardsCrosshair()
{
    if (!GetPawn()) return;

    auto AimingComponent = GetPawn()->FindComponentByClass<UTankAimingComponent>();

    FVector HitLocation;
    bool bGotHitLocation = GetSightRayHitLocation(HitLocation);
    if (bGotHitLocation)
    {
        AimingComponent->AimAt(HitLocation);
    }
}

bool ATankPlayerController::GetSightRayHitLocation(FVector & OutHitLocation) const
{
    int32 ViewportSizeX, ViewportSizeY;
    GetViewportSize(ViewportSizeX, ViewportSizeY);

    auto ScreenLocation = FVector2D(ViewportSizeX * CrosshairXLocation,
        ViewportSizeY * CrosshairYLocation);

    FVector LookDirection;

    if (GetLookDirection(ScreenLocation, LookDirection))
    {
        return GetHitLocation(LookDirection, OutHitLocation);
    }

    return false;
}

bool ATankPlayerController::GetLookDirection(FVector2D ScreenLocation, FVector& LookDirection) const
{
    FVector CameraWorldLocation;
    
    return DeprojectScreenPositionToWorld(ScreenLocation.X, ScreenLocation.Y,
        CameraWorldLocation, LookDirection);
}

bool ATankPlayerController::GetHitLocation(FVector LookDirection, FVector & HitLocation) const
{
    FHitResult HitResult;
    auto StartLocation = PlayerCameraManager->GetCameraLocation();
    auto EndLocation = StartLocation + LookDirection * LineTraceRange;
    if (GetWorld()->LineTraceSingleByChannel(
        HitResult,
        StartLocation,
        EndLocation,
        ECollisionChannel::ECC_Camera))
    {
        HitLocation = HitResult.Location;
        return true;
    }

    HitLocation = FVector(0);
    return false;
}

void ATankPlayerController::SetPawn(APawn * InPawn)
{
    Super::SetPawn(InPawn);

    if (InPawn)
    {
        auto PossessedTank = Cast<ATank>(InPawn);
        if (!PossessedTank) return;

        PossessedTank->OnDeath.AddUniqueDynamic(this, &ATankPlayerController::OnTankDeath);
    }
}

void ATankPlayerController::OnTankDeath()
{
    StartSpectatingOnly();
}
