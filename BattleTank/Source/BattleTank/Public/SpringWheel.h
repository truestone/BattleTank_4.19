

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "SpringWheel.generated.h"

class UPhysicsConstraintComponent;
class USphereComponent;

UCLASS()
class BATTLETANK_API ASpringWheel : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ASpringWheel();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

    void AddDrivingForce(float ForceMagnitude);

private:
    void SetupConstraint();

    UFUNCTION()
    void OnHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit);

    void ApplyForce();

    UPROPERTY(VisibleAnywhere, Category = "Components")
    UPhysicsConstraintComponent* MassWheelConstraint = nullptr;

    UPROPERTY(VisibleAnywhere, Category = "Components")
    USphereComponent* Axle = nullptr;

    UPROPERTY(VisibleAnywhere, Category = "Components")
    UPhysicsConstraintComponent* AxleWheelConstraint = nullptr;

    UPROPERTY(VisibleAnywhere, Category = "Components")
    USphereComponent* Wheel = nullptr;

    float TotalForceMagnitudeThisFrame = 0;
};
