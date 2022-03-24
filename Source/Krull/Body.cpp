// Fill out your copyright notice in the Description page of Project Settings.

#include "Body.h"
#include "ProceduralMeshComponent.h"

// Sets default values.
ABody::ABody()
{
	Mesh = CreateDefaultSubobject<UProceduralMeshComponent>("Mesh");
	Mesh->bUseAsyncCooking = true;
	SetRootComponent(Mesh);
}

// Called when the game starts or when spawned.
void ABody::BeginPlay()
{
	Super::BeginPlay();

	SetupVertices();
}

void ABody::SetupVertices()
{
	for (int JointIndex = 0; JointIndex < JointCount; ++JointIndex)
	{
		for (int SideIndex = 0; SideIndex < SideCount; ++SideIndex)
		{
			//Vertices.Add(FVector::ZeroVector);

			const float Angle{ SideIndex * AngleIncrement };
			const float Radius = 10.0f;

			FVector Vertex = FVector::ZeroVector
				+ Radius * FMath::Cos(Angle) * FVector::YAxisVector
				+ Radius * FMath::Sin(Angle) * FVector::ZAxisVector;

			Vertices.Add(Vertex);
		}
	}
}

void ABody::UpdateVertices(const FTransform Transform)
{
	Vertices.RemoveAt(0, SideCount, false);

	for (int SideIndex = 0; SideIndex < SideCount; ++SideIndex)
	{
		const float Angle{ SideIndex * AngleIncrement };
		const float Radius = 50.0f;

		FVector Vertex = Transform.GetLocation()
			+ Radius * FMath::Cos(Angle) * Transform.GetUnitAxis(EAxis::Type::Y)
			+ Radius * FMath::Sin(Angle) * Transform.GetUnitAxis(EAxis::Type::Z);

		Vertices.Add(Vertex);
	}
}

void ABody::GenerateMesh()
{
	TArray<int32> Triangles;
	TArray<FVector> Normals;
	TArray<FVector2D> UV0;
	TArray<FProcMeshTangent> Tangents;
	TArray<FLinearColor> VertexColors;

	const int SegmentCount{ JointCount - 1 };

	for (int SegmentIndex = 0; SegmentIndex < SegmentCount; ++SegmentIndex)
	{
		for (int SideIndex = 0; SideIndex < SideCount; ++SideIndex)
		{
			const int A{ SegmentIndex * SideCount + SideIndex };
			const int B{ SegmentIndex * SideCount + (SideIndex + 1) % SideCount };
			const int C{ (SegmentIndex + 1) * SideCount + SideIndex };
			const int D{ (SegmentIndex + 1) * SideCount + (SideIndex + 1) % SideCount };

			Triangles.Add(A);
			Triangles.Add(C);
			Triangles.Add(D);
			Triangles.Add(A);
			Triangles.Add(D);
			Triangles.Add(B);
		}
	}

	Mesh->CreateMeshSection_LinearColor(0, Vertices, Triangles, Normals, UV0, VertexColors, Tangents, true);
	Mesh->SetCollisionEnabled(ECollisionEnabled::NoCollision);
}

void ABody::Update(const FTransform Transform, const float Radius)
{
	UpdateVertices(Transform);
	GenerateMesh();
}
