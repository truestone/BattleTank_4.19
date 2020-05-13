

#include "SpringWheel.h"
#include "Components/StaticMeshComponent.h"
#include "Components/SphereComponent.h"
#include "PhysicsEngine/PhysicsConstraintComponent.h"
#include "Engine/World.h"

// Sets default values
ASpringWheel::ASpringWheel()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
    PrimaryActorTick.TickGroup = TG_PostPhysics;

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

    Wheel->SetNotifyRigidBodyCollision(true);
    Wheel->OnComponentHit.AddDynamic(this, &ASpringWheel::OnHit);

    SetupConstraint();
}

// Called every frame
void ASpringWheel::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);

    if (GetWorld()->TickGroup == TG_PostPhysics) {
        TotalForceMagnitudeThisFrame = 0;
    }
}

void ASpringWheel::AddDrivingForce(float ForceMagnitude)
{
    TotalForceMagnitudeThisFrame += ForceMagnitude;
}

void ASpringWheel::SetupConstraint()
{
    if (!GetAttachParentActor()) return;
    UPrimitiveComponent* BodyRoot = Cast<UPrimitiveComponent>(GetAttachParentActor()->GetRootComponent());
    if (!BodyRoot) return;
    MassWheelConstraint->SetConstrainedComponents(BodyRoot, NAME_None, Axle, NAME_None);
    AxleWheelConstraint->SetConstrainedComponents(Axle, NAME_None, Wheel, NAME_None);
}

void ASpringWheel::OnHit(UPrimitiveComponent * HitComponent, AActor * OtherActor, UPrimitiveComponent * OtherComp, FVector NormalImpulse, const FHitResult & Hit)
{
    ApplyForce();
}

void ASpringWheel::ApplyForce()
{
    Wheel->AddForce(Axle->GetForwardVector() * TotalForceMagnitudeThisFrame);
}

