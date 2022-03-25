// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "Curl.generated.h"

UCLASS()
class KRULL_API ACurl : public APawn
{
	GENERATED_BODY()

	UPROPERTY(VisibleAnywhere, Category = Curl)
	int Length{ 1000 };

	UPROPERTY(VisibleAnywhere, Category = Curl)
	int SideCount{ 6 };

	UPROPERTY(VisibleAnywhere, Category = Curl)
	class AHead* Head;

	UPROPERTY(VisibleAnywhere, Category = Curl)
	class ABody* Body;

	UPROPERTY(VisibleAnywhere, Category = Curl)
	UChildActorComponent* HeadComponent;

	UPROPERTY(VisibleAnywhere, Category = Curl)
	UChildActorComponent* BodyComponent;

public:
	// Sets default values for this pawn's properties.
	ACurl();

protected:
	// Called when the game starts or when spawned.
	virtual void BeginPlay() override;

	// Input functions.
	void Yaw(float AxisValue);
	void Pitch(float AxisValue);

public:	
	// Called to bind functionality to input.
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	FVector GetPosition();
	void Update(const float DeltaTime);
};
