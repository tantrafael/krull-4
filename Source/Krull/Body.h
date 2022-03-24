// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Body.generated.h"

UCLASS()
class KRULL_API ABody : public AActor
{
	GENERATED_BODY()

	/** Mesh */
	UPROPERTY(VisibleAnywhere, Category = Curl)
	int SideCount{ 6 };

	UPROPERTY(VisibleAnywhere, Category = Curl)
	int JointCount{ 2000 };

	float AngleIncrement{ 2 * PI / SideCount };
	TArray<FVector> Vertices;

	class UProceduralMeshComponent* Mesh;

public:	
	// Sets default values for this actor's properties.
	ABody();

protected:
	// Called when the game starts or when spawned.
	virtual void BeginPlay() override;

	void SetupVertices();
	void UpdateVertices(const FTransform Transform, const float Radius);
	void GenerateMesh();

public:	
	void Update(const FTransform Transform, const float Radius);
};
