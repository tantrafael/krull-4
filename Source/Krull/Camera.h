// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Camera.generated.h"

UCLASS()
class KRULL_API ACamera : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties.
	ACamera();

	//UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Krull)
	//class UCameraComponent* Camera;

	UPROPERTY(VisibleAnywhere, Category = Krull)
	class UStaticMeshComponent* Body;
	//class UPrimitiveComponent* Body;

protected:
	// Called when the game starts or when spawned.
	virtual void BeginPlay() override;

public:	
	void AddForce(const FVector Force);
	void AddTorque(const FVector Torque);
};
