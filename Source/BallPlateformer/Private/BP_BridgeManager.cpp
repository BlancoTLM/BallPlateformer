// Fill out your copyright notice in the Description page of Project Settings.


#include "BP_BridgeManager.h"

#include "Kismet/KismetMathLibrary.h"

// Sets default values
ABP_BridgeManager::ABP_BridgeManager()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	RootComponent = CreateDefaultSubobject<USceneComponent>(TEXT("Root"));

	PointA = CreateDefaultSubobject<USceneComponent>(TEXT("PointA"));
	PointA->SetupAttachment(RootComponent);

	PointB = CreateDefaultSubobject<USceneComponent>(TEXT("PointB"));
	PointB->SetupAttachment(RootComponent);
}

void ABP_BridgeManager::GenerateBridge()
{
	if (!ConnectorToSpawn || !BeamToSpawn) return;

	if (BeamsArray.Num() > 0)
	{
		for (int i = BeamsArray.Num() - 1; i >= 0; --i)
		{
			if (BeamsArray[i] != nullptr) BeamsArray[i]->Destroy();
		}
		BeamsArray.Empty();
	}

	if (ConnectorsArray.Num() > 0)
	{
		for (int i = ConnectorsArray.Num() - 1; i >= 0; --i)
		{
			if (ConnectorsArray[i] != nullptr) ConnectorsArray[i]->Destroy();
		}
		ConnectorsArray.Empty();
	}

	FVector StartLocation = PointA->GetComponentLocation();
	FVector EndLocation = PointB->GetComponentLocation();

	FVector Direction = EndLocation - StartLocation;
	float BeamLength = Direction.Size() / BeamAmount;
	Direction = Direction.GetSafeNormal();

	FVector CrossDirection = FVector::CrossProduct(FVector::UpVector, Direction);

	ABP_Connector* RightConnector = GetWorld()->SpawnActor<ABP_Connector>(ConnectorToSpawn);
	RightConnector->SetActorLocation(StartLocation + (CrossDirection * ConnectorsDistanceFromCenter) - (Direction * 10));
	RightConnector->IsAnchored = true;

	ABP_Connector* LeftConnector = GetWorld()->SpawnActor<ABP_Connector>(ConnectorToSpawn);
	LeftConnector->SetActorLocation(StartLocation - (CrossDirection * ConnectorsDistanceFromCenter) - (Direction * 10));
	LeftConnector->IsAnchored = true;

	ConnectorsArray.Add(LeftConnector);
	ConnectorsArray.Add(RightConnector);

	RightConnector->AppliedForce = AppliedForce;
	RightConnector->MinDistance = MinDistance;
	RightConnector->Stiffness = Stiffness;

	LeftConnector->AppliedForce = AppliedForce;
	LeftConnector->MinDistance = MinDistance;
	LeftConnector->Stiffness = Stiffness;

	for (int i = 0; i < BeamAmount; i++)
	{
		ABP_Beam* Beam = GetWorld()->SpawnActor<ABP_Beam>(BeamToSpawn);
		FVector Position = StartLocation + (BeamLength * i * Direction);
		Beam->SetActorRotation(UKismetMathLibrary::FindLookAtRotation(Position, Position + CrossDirection));
		Beam->SetActorLocation(Position);

		BeamsArray.Add(Beam);

		Beam->Connectors.Add(LeftConnector);
		Beam->Connectors.Add(RightConnector);

		Beam->MaxStress = MaxStress;

		RightConnector = GetWorld()->SpawnActor<ABP_Connector>(ConnectorToSpawn);
		RightConnector->SetActorLocation(Position + (CrossDirection * ConnectorsDistanceFromCenter) + Direction * 10);

		LeftConnector = GetWorld()->SpawnActor<ABP_Connector>(ConnectorToSpawn);
		LeftConnector->SetActorLocation(Position - (CrossDirection * ConnectorsDistanceFromCenter) + Direction * 10);

		Beam->Connectors.Add(LeftConnector);
		Beam->Connectors.Add(RightConnector);

		ConnectorsArray.Add(LeftConnector);
		ConnectorsArray.Add(RightConnector);

		RightConnector->AppliedForce = AppliedForce;
		RightConnector->MinDistance = MinDistance;
		RightConnector->Stiffness = Stiffness;

		LeftConnector->AppliedForce = AppliedForce;
		LeftConnector->MinDistance = MinDistance;
		LeftConnector->Stiffness = Stiffness;
	}

	RightConnector->IsAnchored = true;
	LeftConnector->IsAnchored = true;

	RightConnector->SetActorLocation(EndLocation + CrossDirection * ConnectorsDistanceFromCenter);
	LeftConnector->SetActorLocation(EndLocation - CrossDirection * ConnectorsDistanceFromCenter);
}