// Fill out your copyright notice in the Description page of Project Settings.

#include "Curl.h"
#include "Head.h"
#include "Body.h"
#include "GameFramework/SpringArmComponent.h"
#include "Camera/CameraComponent.h"

// Sets default values.
ACurl::ACurl()
{
	// Set this actor to call Tick() every frame. You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	RootComponent = CreateDefaultSubobject<USceneComponent>(TEXT("RootComponent"));

	HeadComponent = CreateDefaultSubobject<UChildActorComponent>(TEXT("Head"));
	HeadComponent->RegisterComponent();
	HeadComponent->SetupAttachment(RootComponent);
	HeadComponent->SetChildActorClass(AHead::StaticClass());
	HeadComponent->CreateChildActor();

	BodyComponent = CreateDefaultSubobject<UChildActorComponent>(TEXT("Body"));
	BodyComponent->RegisterComponent();
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
	if (Head == nullptr)
	{
		return;
	}

	const FVector Torque = AxisValue * FVector::ZAxisVector;
	Head->Turn(Torque);
}

void ACurl::Pitch(float AxisValue)
{
	if (Head == nullptr)
	{
		return;
	}

	const FVector Torque = AxisValue * FVector::YAxisVector;
	Head->Turn(Torque);
}

// Called every frame.
void ACurl::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	// TODO: Assert

	if (Head == nullptr || Body == nullptr)
	{
		return;
	}

	Head->Update();

	const FTransform Transform = Head->GetTransform();
	FVector AngularVelocity = Head->GetAngularVelocity();
	//const float Radius = 10.0f;
	//const float Radius = 10.0f + 4.0f * AngularVelocity.Size();
	//const float Radius = 20.0f + 0.5f * AngularVelocity.Size();
	const float Radius = 10.0f + 2.0f * AngularVelocity.Size();
	//const float Radius = 4000.0f / (AngularVelocity.Size() + 10.0f);

	Body->Update(Transform, Radius);
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
