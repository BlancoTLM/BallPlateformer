// Fill out your copyright notice in the Description page of Project Settings.


#include "BP_BridgeManager.h"

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

	FVector StartLocation = PointA->GetComponentLocation();
	FVector EndLocation = PointB->GetComponentLocation();

	FVector Direction = EndLocation - StartLocation;
	float BeamLength = Direction.Size() / BeamAmount;
	Direction = Direction.GetSafeNormal();

	ABP_Connector* CurrentConnector = GetWorld()->SpawnActor<ABP_Connector>();
	CurrentConnector->SetActorLocation(StartLocation);
	CurrentConnector->IsAnchored = true;

	// Here
}