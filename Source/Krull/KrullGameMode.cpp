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

	Curl->Update(DeltaTime);

	const FVector CurlPosition{ Curl->GetPosition() };
	const FVector CurlDirection{ Curl->GetOrientation().GetUnitAxis(EAxis::Type::X) };
	const FVector CameraTargetPosition{ CurlPosition - 400.0f * CurlDirection };
	const FVector DeltaPlacementPosition{ CameraTargetPosition - Camera->GetActorLocation() };
	const FVector Force{ 1000.0f * DeltaPlacementPosition };
	Camera->AddForce(Force);

	const FVector DeltaLookatPosition{ CurlPosition - Camera->GetActorLocation() };
	const FVector CameraTargetDirection{ DeltaLookatPosition.GetSafeNormal() };
	const FVector CameraForwardAxis{ Camera->GetActorForwardVector() };
	const FVector Torque{ 10000000.0f * FVector::CrossProduct(CameraForwardAxis, CameraTargetDirection) };
	Camera->AddTorque(Torque);
}
