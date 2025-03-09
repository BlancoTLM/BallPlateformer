// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "BA_MoveingPlateform.generated.h"

UCLASS()
class BALLPLATEFORMER_API ABA_MoveingPlateform : public AActor
{
	GENERATED_BODY()
	
public:	
	ABA_MoveingPlateform();

protected:
	virtual void BeginPlay() override;

public:	
	virtual void Tick(float DeltaTime) override;
	FVector GetPlatformVelocity() const;

private:
	UPROPERTY(EditAnywhere, Category = "Settings")
	FVector StartPoint;

	UPROPERTY(EditAnywhere, Category = "Settings")
	FVector EndPoint;

	UPROPERTY(EditAnywhere, Category = "Settings")
	float Speed = 200.0f;

	float InterpAlpha = 0.0f;
	bool bMovingForward = true;

};