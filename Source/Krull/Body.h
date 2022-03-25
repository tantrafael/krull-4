// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Body.generated.h"

UCLASS()
class KRULL_API ABody : public AActor
{
	GENERATED_BODY()

	UPROPERTY(VisibleAnywhere, Category = Curl)
	int SideCount;

	UPROPERTY(VisibleAnywhere, Category = Curl)
	int JointCount;

	UPROPERTY(VisibleAnywhere, Category = Curl)
	float SideAngle;

	UPROPERTY(VisibleAnywhere, Category = Curl)
	TArray<FVector> Vertices;

	// Runtime-generated tubular mesh.
	UPROPERTY(VisibleAnywhere, Category = Curl)
	class UProceduralMeshComponent* Mesh;

public:	
	// Sets default values for this actor's properties.
	ABody();

protected:
	// Called when the game starts or when spawned.
	virtual void BeginPlay() override;

	void InitializeVertices();
	void UpdateVertices(const FTransform Transform, const float Radius);
	void GenerateMesh();

public:	
	void Update(const FTransform Transform, const float Radius);
};
