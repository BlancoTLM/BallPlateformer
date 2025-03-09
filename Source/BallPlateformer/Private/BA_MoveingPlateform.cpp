// Fill out your copyright notice in the Description page of Project Settings.

#include "BA_MoveingPlateform.h"

ABA_MoveingPlateform::ABA_MoveingPlateform()
{
	PrimaryActorTick.bCanEverTick = true;
}

void ABA_MoveingPlateform::BeginPlay()
{
	Super::BeginPlay();

	StartPoint = GetActorLocation();
	EndPoint = StartPoint + FVector(500.0f, 0.0f, 0.0f);
}

void ABA_MoveingPlateform::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	FVector NewLocation;
	float MoveStep = Speed * DeltaTime;

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

	NewLocation = FMath::Lerp(StartPoint, EndPoint, InterpAlpha);
	SetActorLocation(NewLocation);
}

FVector ABA_MoveingPlateform::GetPlatformVelocity() const
{
	FVector Direction = (EndPoint - StartPoint).GetSafeNormal();
	return Direction * Speed * (bMovingForward ? 1.0f : -1.0f);
}