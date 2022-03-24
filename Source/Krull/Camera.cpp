// Fill out your copyright notice in the Description page of Project Settings.


#include "Camera.h"
#include "Camera/CameraComponent.h"

// Sets default values.
ACamera::ACamera()
{
	UE_LOG(LogTemp, Warning, TEXT("ACamera::ACamera()"));
	
	static ConstructorHelpers::FObjectFinder<UStaticMesh> BallMesh(TEXT("/Game/Meshes/BallMesh.BallMesh"));

	Body = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Body"));
	//Body = CreateDefaultSubobject<UPrimitiveComponent>(TEXT("Body"));
	Body->SetStaticMesh(BallMesh.Object);
	Body->BodyInstance.SetCollisionProfileName(UCollisionProfile::PhysicsActor_ProfileName);
	Body->SetSimulatePhysics(true);
	Body->SetLinearDamping(1.0f);
	Body->SetAngularDamping(1.0f);
	Body->SetEnableGravity(false);
	Body->BodyInstance.MassScale = 1.0f;
	Body->BodyInstance.MaxAngularVelocity = 1000.0f;
	Body->SetNotifyRigidBodyCollision(false);
	Body->SetCollisionEnabled(ECollisionEnabled::PhysicsOnly);
	//Body->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	//Body->bHiddenInGame = true;
	//Body->SetupAttachment(RootComponent);
	SetRootComponent(Body);

	/*
	Camera = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
	Camera->bAutoActivate = true;
	*/
}

// Called when the game starts or when spawned
void ACamera::BeginPlay()
{
	Super::BeginPlay();

	Body->SetLinearDamping(2.0f);
	Body->SetAngularDamping(4.0f);

	GetWorld()->GetFirstPlayerController()->SetViewTarget(this);
}

void ACamera::AddForce(const FVector Force)
{
	Body->AddForce(Force);
}

void ACamera::AddTorque(const FVector Torque)
{
	Body->AddTorque(Torque);
}
