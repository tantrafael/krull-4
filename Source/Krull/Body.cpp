// Fill out your copyright notice in the Description page of Project Settings.

#include "Body.h"
#include "ProceduralMeshComponent.h"

// Sets default values.
ABody::ABody()
{
	SideCount = 6;
	JointCount = 2000;
	SideAngle = 2 * PI / SideCount;

	Mesh = CreateDefaultSubobject<UProceduralMeshComponent>("Mesh");
	Mesh->bUseAsyncCooking = true;
	SetRootComponent(Mesh);
}

// Called when the game starts or when spawned.
void ABody::BeginPlay()
{
	Super::BeginPlay();

	InitializeVertices();
}

void ABody::InitializeVertices()
{
	/*
	const float Radius = 50.0f;

	for (int JointIndex = 0; JointIndex < JointCount; ++JointIndex)
	{
		for (int SideIndex = 0; SideIndex < SideCount; ++SideIndex)
		{
			//Vertices.Add(FVector::ZeroVector);

			const float Angle{ SideIndex * SideAngle };

			FVector Vertex = FVector::ZeroVector
			//FVector Vertex = JointIndex * FVector::XAxisVector
				+ Radius * FMath::Cos(Angle) * FVector::YAxisVector
				+ Radius * FMath::Sin(Angle) * FVector::ZAxisVector;

			Vertices.Add(Vertex);
		}
	}
	*/

	for (int i = 0; i < JointCount * SideCount; ++i)
	{
		Vertices.Add(FVector::ZeroVector);
	}
}

void ABody::UpdateVertices(const FTransform Transform, const float Radius)
{
	Vertices.RemoveAt(0, SideCount, false);

	for (int SideIndex = 0; SideIndex < SideCount; ++SideIndex)
	{
		const float Angle{ SideIndex * SideAngle };

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
			const int AnteriorJointAnteriorVertex{ SegmentIndex * SideCount + SideIndex };
			const int AnteriorJointPosteriorVertex{ SegmentIndex * SideCount + (SideIndex + 1) % SideCount };
			const int PosteriorJointAnteriorVertex{ (SegmentIndex + 1) * SideCount + SideIndex };
			const int PosteriorJointPosteriorVertex{ (SegmentIndex + 1) * SideCount + (SideIndex + 1) % SideCount };

			Triangles.Add(AnteriorJointAnteriorVertex);
			Triangles.Add(PosteriorJointAnteriorVertex);
			Triangles.Add(PosteriorJointPosteriorVertex);
			Triangles.Add(AnteriorJointAnteriorVertex);
			Triangles.Add(PosteriorJointPosteriorVertex);
			Triangles.Add(AnteriorJointPosteriorVertex);
		}
	}

	Mesh->CreateMeshSection_LinearColor(0, Vertices, Triangles, Normals, UV0, VertexColors, Tangents, true);
	Mesh->SetCollisionEnabled(ECollisionEnabled::NoCollision);
}

void ABody::Update(const FTransform Transform, const float Radius)
{
	UpdateVertices(Transform, Radius);
	GenerateMesh();
}
