// Fill out your copyright notice in the Description page of Project Settings.

#include "Curl.h"
#include "Head.h"
#include "Body.h"
#include "GameFramework/SpringArmComponent.h"
#include "Camera/CameraComponent.h"

// Sets default values.
ACurl::ACurl()
{
	RootComponent = CreateDefaultSubobject<USceneComponent>(TEXT("RootComponent"));

	HeadComponent = CreateDefaultSubobject<UChildActorComponent>(TEXT("Head"));
	HeadComponent->SetupAttachment(RootComponent);
	HeadComponent->SetChildActorClass(AHead::StaticClass());
	HeadComponent->CreateChildActor();

	BodyComponent = CreateDefaultSubobject<UChildActorComponent>(TEXT("Body"));
	BodyComponent->SetupAttachment(RootComponent);
	BodyComponent->SetChildActorClass(ABody::StaticClass());
	BodyComponent->CreateChildActor();
}

// Called when the game starts or when spawned.
void ACurl::BeginPlay()
{
	Super::BeginPlay();

	Head = Cast<AHead>(HeadComponent->GetChildActor());
	Body = Cast<ABody>(BodyComponent->GetChildActor());
}

void ACurl::Yaw(float AxisValue)
{
	// TODO: Assert Head.
	if (Head == nullptr)
	{
		return;
	}

	const FVector Torque = AxisValue * FVector::ZAxisVector;
	Head->Turn(Torque);
}

void ACurl::Pitch(float AxisValue)
{
	// TODO: Assert Head.
	if (Head == nullptr)
	{
		return;
	}

	const FVector Torque = AxisValue * FVector::YAxisVector;
	Head->Turn(Torque);
}

void ACurl::SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent)
{
	// Set up gameplay key bindings.
	PlayerInputComponent->BindAxis("Yaw", this, &ACurl::Yaw);
	PlayerInputComponent->BindAxis("Pitch", this, &ACurl::Pitch);
}

FVector ACurl::GetPosition()
{
	return Head->GetPosition();
}

FTransform ACurl::GetOrientation()
{
	return Head->GetOrientation();
}

void ACurl::Update(const float DeltaTime)
{
	// TODO: Assert Head and Body.
	if (Head == nullptr || Body == nullptr)
	{
		return;
	}

	Head->Update();

	const FTransform Transform = Head->GetOrientation();
	FVector AngularVelocity = Head->GetAngularVelocity();
	const float Radius = 20.0f + 1.0f * AngularVelocity.Size();
	//const float Radius = 10.0f + 2.0f * AngularVelocity.Size();

	Body->Update(Transform, Radius);
}