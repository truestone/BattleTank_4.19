// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "TankAIController.generated.h"

class ATank;

UCLASS()
class BATTLETANK_API ATankAIController : public AAIController
{
	GENERATED_BODY()

protected:
    UPROPERTY(EditDefaultsOnly, Category = "Setup")
    float AcceptanceRadius = 3000;

private:
    virtual void Tick(float DeltaSeconds) override;
};
