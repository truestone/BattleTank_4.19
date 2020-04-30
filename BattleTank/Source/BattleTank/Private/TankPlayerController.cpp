// Fill out your copyright notice in the Description page of Project Settings.

#include "TankPlayerController.h"

ATank* ATankPlayerController::GetControlledTank() const
{
	return Cast<ATank>(GetPawn());
}

void ATankPlayerController::BeginPlay()
{
	Super::BeginPlay();
	auto ControlledTank = GetControlledTank();
	if (!ControlledTank)
	{
		UE_LOG(LogTemp, Warning, TEXT("TankPlayerController not possessing a tank"));
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("TankPlayerController possessing: %s"),
			*ControlledTank->GetName());
	}
}

void ATankPlayerController::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);

    AimTowardsCrosshair();
}

void ATankPlayerController::AimTowardsCrosshair()
{
    if (!GetControlledTank()) { return; }

    FVector HitLocation;
    if (GetSightRayHitLocation(HitLocation))
    {
        //UE_LOG(LogTemp, Warning, TEXT("HitLocation: %s"), *HitLocation.ToString());
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
        UE_LOG(LogTemp, Warning, TEXT("Look Direction: %s"), *LookDirection.ToString());
    }

    // TODO: Line-trace along that LookDirection, and see what we hit
    OutHitLocation = FVector(1.0f);
    return true;
}

bool ATankPlayerController::GetLookDirection(FVector2D ScreenLocation, FVector& LookDirection) const
{
    FVector CameraWorldLocation;

    return DeprojectScreenPositionToWorld(ScreenLocation.X, ScreenLocation.Y,
        CameraWorldLocation, LookDirection);
}
