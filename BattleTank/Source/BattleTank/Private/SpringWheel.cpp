

#include "SpringWheel.h"
#include "Components/StaticMeshComponent.h"
#include "Components/SphereComponent.h"
#include "PhysicsEngine/PhysicsConstraintComponent.h"

// Sets default values
ASpringWheel::ASpringWheel()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

    MassWheelConstraint = CreateDefaultSubobject<UPhysicsConstraintComponent>(FName("Mass Wheel Constraint"));
    SetRootComponent(MassWheelConstraint);

    Axle = CreateDefaultSubobject<USphereComponent>(FName("Axle"));
    Axle->AttachToComponent(MassWheelConstraint, FAttachmentTransformRules::KeepRelativeTransform);

    AxleWheelConstraint = CreateDefaultSubobject<UPhysicsConstraintComponent>(FName("Axle Wheel Constraint"));
    AxleWheelConstraint->AttachToComponent(Axle, FAttachmentTransformRules::KeepRelativeTransform);

    Wheel = CreateDefaultSubobject<USphereComponent>(FName("Wheel"));
    Wheel->AttachToComponent(Axle, FAttachmentTransformRules::KeepRelativeTransform);
}

// Called when the game starts or when spawned
void ASpringWheel::BeginPlay()
{
	Super::BeginPlay();

    SetupConstraint();
}

// Called every frame
void ASpringWheel::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ASpringWheel::AddDrivingForce(float ForceMagnitude)
{
    Wheel->AddForce(Axle->GetForwardVector() * ForceMagnitude);
}

void ASpringWheel::SetupConstraint()
{
    if (!GetAttachParentActor()) return;
    UPrimitiveComponent* BodyRoot = Cast<UPrimitiveComponent>(GetAttachParentActor()->GetRootComponent());
    if (!BodyRoot) return;
    MassWheelConstraint->SetConstrainedComponents(BodyRoot, NAME_None, Axle, NAME_None);
    AxleWheelConstraint->SetConstrainedComponents(Axle, NAME_None, Wheel, NAME_None);
}

