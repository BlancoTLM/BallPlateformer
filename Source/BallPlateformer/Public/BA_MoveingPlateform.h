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
	// Sets default values for this actor's properties
	ABA_MoveingPlateform();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	FVector GetPlatformVelocity() const;

private:
	// Points de déplacement
	UPROPERTY(EditAnywhere, Category = "Settings")
	FVector StartPoint;

	UPROPERTY(EditAnywhere, Category = "Settings")
	FVector EndPoint;

	UPROPERTY(EditAnywhere, Category = "Settings")
	float Speed = 200.0f; // Vitesse de déplacement

	float InterpAlpha = 0.0f;
	bool bMovingForward = true;

};
