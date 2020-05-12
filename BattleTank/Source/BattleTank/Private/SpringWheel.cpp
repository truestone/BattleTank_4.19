

#include "SpringWheel.h"
#include "Components/StaticMeshComponent.h"
#include "PhysicsEngine/PhysicsConstraintComponent.h"

// Sets default values
ASpringWheel::ASpringWheel()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

    MassWheelConstraint = CreateDefaultSubobject<UPhysicsConstraintComponent>(FName("Mass Wheel Constraint"));
    SetRootComponent(MassWheelConstraint);

    Mass = CreateDefaultSubobject<UStaticMeshComponent>(FName("Mass"));
    Mass->AttachToComponent(MassWheelConstraint, FAttachmentTransformRules::KeepRelativeTransform);

    Wheel = CreateDefaultSubobject<UStaticMeshComponent>(FName("Wheel"));
    Wheel->AttachToComponent(MassWheelConstraint, FAttachmentTransformRules::KeepRelativeTransform);
}

// Called when the game starts or when spawned
void ASpringWheel::BeginPlay()
{
	Super::BeginPlay();

    if (GetAttachParentActor())
    {
        UE_LOG(LogTemp, Warning, TEXT("SpringWheel: Parent Actor Not Null: %s"), *GetAttachParentActor()->GetName());
    }
    else
    {
        UE_LOG(LogTemp, Warning, TEXT("SpringWheel: Parent Actor Null"));
    }
}

// Called every frame
void ASpringWheel::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

