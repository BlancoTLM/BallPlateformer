// Fill out your copyright notice in the Description page of Project Settings.

#include "BP_Connector.h"

// Sets default values
ABP_Connector::ABP_Connector()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
}

void ABP_Connector::BeginPlay()
{
	Super::BeginPlay();
	
	MeshComponent = FindComponentByClass<UStaticMeshComponent>();
	if (!MeshComponent)
	{
		UE_LOG(LogTemp, Warning, TEXT("No mesh found in connector"));
		return;
	}

	MeshComponent->SetSimulatePhysics(false);
	MeshComponent->SetCollisionEnabled(ECollisionEnabled::Type::NoCollision);
}

void ABP_Connector::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (IsAnchored) return;
	
	FVector Position = FVector(0, 0, 0);
	for (ABP_Beam* Beam : ConnectedBeams)
	{
		if (Beam)
		{
			Position += Beam->GetCornerPosition(this);
		}
	}

	Position /= ConnectedBeams.Num();

	SetActorLocation(Position);
}

FVector ABP_Connector::GetForce(FVector Position)
{
	FVector Direction = MeshComponent->GetComponentLocation() - Position;
	
	float Distance = Direction.Size();
	Direction.Normalize();
	float StretchFactor = Distance - MinDistance;
	StretchFactor = FMath::Clamp(StretchFactor, -Stiffness, Stiffness);
	
	return AppliedForce * StretchFactor * Direction;
}