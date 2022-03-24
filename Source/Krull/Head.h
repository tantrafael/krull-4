// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Head.generated.h"

UCLASS()
class KRULL_API AHead : public AActor
{
	GENERATED_BODY()

	// StaticMesh used for the director
	UPROPERTY(VisibleAnywhere, Category = Krull)
	class UStaticMeshComponent* Director;

	// StaticMesh used for the positioner
	UPROPERTY(VisibleAnywhere, Category = Krull)
	class UStaticMeshComponent* Positioner;

public:
	// Sets default values for this actor's properties
	AHead();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	FVector GetPosition();
	FTransform GetTransform();
	FVector GetAngularVelocity();
	void Turn(const FVector Torque);
	void Update();
};
