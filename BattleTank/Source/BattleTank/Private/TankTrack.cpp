// Fill out your copyright notice in the Description page of Project Settings.

#include "TankTrack.h"
#include "Components/SceneComponent.h"
#include "SpawnPoint.h"
#include "SpringWheel.h"

UTankTrack::UTankTrack()
{
    PrimaryComponentTick.bCanEverTick = true;
}

void UTankTrack::BeginPlay()
{
    Super::BeginPlay();
}

TArray<ASpringWheel*> UTankTrack::GetWheels() const
{
    TArray<ASpringWheel*> ResultArray;
    TArray<USceneComponent*> Children;
    GetChildrenComponents(true, Children);

    for (auto Child : Children)
    {
        auto SpawnPointChild = Cast<USpawnPoint>(Child);
        if (!SpawnPointChild) continue;

        AActor* SpawnedChild = SpawnPointChild->GetSpawnedActor();
        auto SpringWheel = Cast<ASpringWheel>(SpawnedChild);
        if (!SpringWheel) continue;

        ResultArray.Add(SpringWheel);
    }
    return ResultArray;
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


