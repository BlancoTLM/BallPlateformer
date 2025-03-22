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

	for (ABP_Beam* Beam : ConnectedBeams)
	{
		Beam->Connectors.Add(this);
	}
}

void ABP_Connector::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	FVector Position = FVector(0, 0, 0);
	for (ABP_Beam* Beam : ConnectedBeams)
	{
		if (Beam)
		{
			FVector Direction = MeshComponent->GetComponentLocation() - Beam->MeshComponent->GetComponentLocation();
		
			Beam->MeshComponent->AddForce(Direction * AppliedForce, NAME_None, true);

			Position += Beam->MeshComponent->GetComponentLocation();
		}
	}

	Position /= ConnectedBeams.Num();

	FVector Pos = GetActorLocation();
	Pos.Z = Position.Z;

	SetActorLocation(Pos);
}