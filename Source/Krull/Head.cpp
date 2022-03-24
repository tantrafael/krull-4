// Fill out your copyright notice in the Description page of Project Settings.

#include "Head.h"

// Sets default values.
AHead::AHead()
{
	RootComponent = CreateDefaultSubobject<USceneComponent>(TEXT("RootComponent"));

	// TODO: Fix texture.
	static ConstructorHelpers::FObjectFinder<UStaticMesh> BallMesh(TEXT("/Game/Meshes/BallMesh.BallMesh"));

	// Create mesh component for the director.
	Director = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Director"));
	Director->SetStaticMesh(BallMesh.Object);
	Director->BodyInstance.SetCollisionProfileName(UCollisionProfile::PhysicsActor_ProfileName);
	Director->SetSimulatePhysics(true);
	Director->SetLinearDamping(1.0f);
	Director->SetAngularDamping(1.0f);
	Director->SetEnableGravity(false);
	Director->BodyInstance.MassScale = 1.0f;
	Director->BodyInstance.MaxAngularVelocity = 1000.0f;
	Director->SetNotifyRigidBodyCollision(false);
	Director->SetCollisionEnabled(ECollisionEnabled::PhysicsOnly);
	//Director->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	//Director->bHiddenInGame = true;
	Director->SetupAttachment(RootComponent);

	// Create mesh component for the positioner.
	Positioner = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Positioner"));
	Positioner->SetStaticMesh(BallMesh.Object);
	Positioner->SetSimulatePhysics(false);
	Positioner->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	Positioner->SetNotifyRigidBodyCollision(false);
	Positioner->SetupAttachment(RootComponent);
}

// Called when the game starts or when spawned.
void AHead::BeginPlay()
{
	Super::BeginPlay();

	//Director->SetAngularDamping(1.0f);
	Director->SetAngularDamping(2.0f);
}

FVector AHead::GetPosition()
{
	return Positioner->GetComponentLocation();
}

FTransform AHead::GetTransform()
{
	return Positioner->GetComponentTransform();
}

FVector AHead::GetAngularVelocity()
{
	return Director->GetPhysicsAngularVelocityInRadians();
}

void AHead::Turn(const FVector Torque)
{
	const FVector T = 50000000.0f * Torque;
	Director->AddTorqueInRadians(T);
}

void AHead::Update()
{
	const FVector Torque = 400000000.0f * FMath::VRand();
	//Director->AddTorqueInRadians(Torque);

	const FQuat Orientation = Director->GetComponentQuat();
	//const FVector ForwardDirection = Orientation.GetAxisX();
	const FVector CurrentPosition = Positioner->GetComponentLocation();
	//const FVector UpdatedPosition = CurrentPosition + 100.0f * ForwardDirection;
	const FVector UpdatedPosition = CurrentPosition + 100.0f * Orientation.GetAxisX();

	Positioner->SetWorldLocationAndRotation(UpdatedPosition, Orientation);
}
