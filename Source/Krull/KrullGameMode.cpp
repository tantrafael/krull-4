// Fill out your copyright notice in the Description page of Project Settings.

#include "KrullGameMode.h"
#include "Curl.h"
#include "Camera.h"
#include "Kismet/GameplayStatics.h"

AKrullGameMode::AKrullGameMode()
{
	UE_LOG(LogTemp, Warning, TEXT("AKrullGameMode()"));

	PrimaryActorTick.bCanEverTick = true;

	DefaultPawnClass = ACurl::StaticClass();
}

void AKrullGameMode::BeginPlay()
{
	Super::BeginPlay();

	AActor* CameraActor = UGameplayStatics::GetActorOfClass(GetWorld(), ACamera::StaticClass());
	Camera = Cast<ACamera>(CameraActor);

	AActor* CurlActor = UGameplayStatics::GetActorOfClass(GetWorld(), ACurl::StaticClass());
	Curl = Cast<ACurl>(CurlActor);
}

void AKrullGameMode::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	FVector DeltaPosition = Curl->GetPosition() - Camera->GetActorLocation();
	FVector Force = 400.0f * DeltaPosition;
	Camera->AddForce(Force);
	//Camera->Body->AddForce(Force);

	FVector CameraForward = Camera->GetActorForwardVector();
	//FVector F = Camera->GetActorForwardVector();
	FVector Torque = 1000.0f * FVector::CrossProduct(CameraForward, DeltaPosition);
	//Camera->Body->AddTorqueInRadians(200.0f * Torque);
	//Camera->Body->AddTorqueInRadians(Torque);
	Camera->AddTorque(Torque);
}
