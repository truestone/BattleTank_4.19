// Fill out your copyright notice in the Description page of Project Settings.

#include "TankTrack.h"
#include "SpringWheel.h"

UTankTrack::UTankTrack()
{
    PrimaryComponentTick.bCanEverTick = true;
}

void UTankTrack::BeginPlay()
{
    Super::BeginPlay();
}

TArray<class ASpringWheel*> UTankTrack::GetWheels() const
{
    return TArray<class ASpringWheel*>();
}

void UTankTrack::SetThrottle(float Throttle)
{
    auto ForceApplied = Throttle * TrackMaxDrivingForce;
    auto Wheels = GetWheels();
    auto ForcePerWheel = ForceApplied / Wheels.Num();
    for (auto Wheel : Wheels)
    {
        Wheel->AddDrivingForce(ForcePerWheel);
    }
}


