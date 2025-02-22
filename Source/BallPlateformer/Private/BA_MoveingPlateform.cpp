// Fill out your copyright notice in the Description page of Project Settings.

#include "BA_MoveingPlateform.h"

// Sets default values
ABA_MoveingPlateform::ABA_MoveingPlateform()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
}

// Called when the game starts or when spawned
void ABA_MoveingPlateform::BeginPlay()
{
	Super::BeginPlay();

	StartPoint = GetActorLocation();
	EndPoint = StartPoint + FVector(500.0f, 0.0f, 0.0f); // Modifier selon le trajet souhaité
}

// Called every frame
void ABA_MoveingPlateform::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	FVector NewLocation;
	float MoveStep = Speed * DeltaTime; // Distance par frame

	if (bMovingForward)
	{
		InterpAlpha += MoveStep / FVector::Dist(StartPoint, EndPoint);
		if (InterpAlpha >= 1.0f)
		{
			InterpAlpha = 1.0f;
			bMovingForward = false;
		}
	}
	else
	{
		InterpAlpha -= MoveStep / FVector::Dist(StartPoint, EndPoint);
		if (InterpAlpha <= 0.0f)
		{
			InterpAlpha = 0.0f;
			bMovingForward = true;
		}
	}

	// Interpolation entre les points
	NewLocation = FMath::Lerp(StartPoint, EndPoint, InterpAlpha);
	SetActorLocation(NewLocation);
}

FVector ABA_MoveingPlateform::GetPlatformVelocity() const
{
	FVector Direction = (EndPoint - StartPoint).GetSafeNormal();
	return Direction * Speed * (bMovingForward ? 1.0f : -1.0f);
}

