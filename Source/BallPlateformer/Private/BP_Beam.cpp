// Fill out your copyright notice in the Description page of Project Settings.

#include "BP_Beam.h"
#include "BP_Connector.h"

// Sets default values
ABP_Beam::ABP_Beam()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
}

void ABP_Beam::BeginPlay()
{
	Super::BeginPlay();
	
	MeshComponent = FindComponentByClass<UStaticMeshComponent>();
	if (!MeshComponent)
	{
		UE_LOG(LogTemp, Warning, TEXT("No mesh found in beam"));
		return;
	}

	MeshComponent->SetSimulatePhysics(true);
	MeshComponent->SetCollisionEnabled(ECollisionEnabled::Type::QueryAndPhysics);
	MeshComponent->BodyInstance.bLockYRotation = true;
	MeshComponent->BodyInstance.bLockZRotation = true;
}

void ABP_Beam::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	for (ABP_Connector* Connector : Connectors)
	{
		FVector Direction = Connector->MeshComponent->GetComponentLocation() - MeshComponent->GetComponentLocation();

		if (Direction.X > 0)
		{
		}
		else
		{
		}
	}
}