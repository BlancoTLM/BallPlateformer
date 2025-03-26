// Fill out your copyright notice in the Description page of Project Settings.

#include "BP_Beam.h"
#include "BP_Connector.h"

// Sets default values
ABP_Beam::ABP_Beam()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	RootComponent = CreateDefaultSubobject<USceneComponent>(TEXT("SurMaRoute"));
	MeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Émeshé"));
	MeshComponent->SetSimulatePhysics(true);
	MeshComponent->SetupAttachment(RootComponent);

	TopLeft = CreateDefaultSubobject<USceneComponent>(TEXT("TopLeft"));
	TopLeft->SetupAttachment(MeshComponent);
	TopRight = CreateDefaultSubobject<USceneComponent>(TEXT("TopRight"));
	TopRight->SetupAttachment(MeshComponent);
	BotLeft = CreateDefaultSubobject<USceneComponent>(TEXT("BotLeft"));
	BotLeft->SetupAttachment(MeshComponent);
	BotRight = CreateDefaultSubobject<USceneComponent>(TEXT("BotRight"));
	BotRight->SetupAttachment(MeshComponent);
}

void ABP_Beam::BeginPlay()
{
	Super::BeginPlay();

	ConnectConnectors();

	if (!Material) return;
	DynamicMaterial = UMaterialInstanceDynamic::Create(Material, this);
	MeshComponent->SetMaterial(0, DynamicMaterial);
}

void ABP_Beam::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	FVector AllForces = FVector::ZeroVector;
	FVector CurrentForce = FVector::ZeroVector;
	
	if (TopLeftConnector)
	{
		CurrentForce = TopLeftConnector->GetForce(TopLeft->GetComponentLocation());
		MeshComponent->AddForceAtLocation(CurrentForce, TopLeft->GetComponentLocation());
		AllForces += CurrentForce;
	}
	if (TopRightConnector)
	{
		CurrentForce = TopRightConnector->GetForce(TopRight->GetComponentLocation());
		MeshComponent->AddForceAtLocation(CurrentForce, TopRight->GetComponentLocation());
		AllForces += CurrentForce;
	}
	if (BotLeftConnector)
	{
		CurrentForce = BotLeftConnector->GetForce(BotLeft->GetComponentLocation());
		MeshComponent->AddForceAtLocation(CurrentForce, BotLeft->GetComponentLocation());
		AllForces += CurrentForce;
	}
	if (BotRightConnector)
	{
		CurrentForce = BotRightConnector->GetForce(BotRight->GetComponentLocation());
		MeshComponent->AddForceAtLocation(CurrentForce, BotRight->GetComponentLocation());
		AllForces += CurrentForce;
	}

	AllForces = AllForces / 4;
	float ZeroToOne = FMath::Clamp(AllForces.Size() / MaxStress, 0.0f,1.0f);
	if (DynamicMaterial)
	{
		DynamicMaterial->SetScalarParameterValue(FName("LerpValue"), ZeroToOne);
	}

	if (ZeroToOne == 1)
	{
		Timer += DeltaTime;
		if (Timer < 1) return;

		for (ABP_Connector* Connector : Connectors)
		{
			if (Connector)
				Connector->ConnectedBeams.Remove(this);
		}
		Destroy();
	}
	else
		Timer = 0;
}

FVector ABP_Beam::GetCornerPosition(const ABP_Connector* Connector)
{
	if (Connector == TopLeftConnector)
		return TopLeft->GetComponentLocation();
	
	if (Connector == TopRightConnector)
		return TopRight->GetComponentLocation();

	if (Connector == BotLeftConnector)
		return BotLeft->GetComponentLocation();

	if (Connector == BotRightConnector)
		return BotRight->GetComponentLocation();

	return FVector::ZeroVector;
}

void ABP_Beam::ConnectConnectors()
{
	for (ABP_Connector* Connector : Connectors)
	{
		if (!Connector) continue;

		Connector->ConnectedBeams.Add(this);
		
		float Distance = 1000000000000000000000000000000000000.0f;
		int Index = -1;

		float DistanceTemp = FVector::Distance(Connector->GetActorLocation(), TopLeft->GetComponentLocation());
		if (DistanceTemp < Distance)
		{
			Distance = DistanceTemp;
			Index = 0;
		}
		
		DistanceTemp = FVector::Distance(Connector->GetActorLocation(), TopRight->GetComponentLocation());
		if (DistanceTemp < Distance)
		{
			Distance = DistanceTemp;
			Index = 1;
		}
		
		DistanceTemp = FVector::Distance(Connector->GetActorLocation(), BotLeft->GetComponentLocation());
		if (DistanceTemp < Distance)
		{
			Distance = DistanceTemp;
			Index = 2;
		}
		
		DistanceTemp = FVector::Distance(Connector->GetActorLocation(), BotRight->GetComponentLocation());
		if (DistanceTemp < Distance)
		{
			Index = 3;
		}

		switch (Index)
		{
		case 0:
			TopLeftConnector = Connector;
			break;
		case 1:
			TopRightConnector = Connector;
			break;
		case 2:
			BotLeftConnector = Connector;
			break;
		case 3:
			BotRightConnector = Connector;
			break;
		}
	}
}