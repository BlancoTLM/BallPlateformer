// Fill out your copyright notice in the Description page of Project Settings.

#include "BP_Anchor.h"

// Sets default values
ABP_Anchor::ABP_Anchor()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
}

void ABP_Anchor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	for (ABP_Beam* Beam : ConnectedBeams)
	{
		FVector Direction = MeshComponent->GetComponentLocation() - Beam->MeshComponent->GetComponentLocation();
		
		Beam->MeshComponent->AddForce(Direction * AppliedForce, NAME_None, true);
	}
}

void ABP_Anchor::BeginPlay()
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
