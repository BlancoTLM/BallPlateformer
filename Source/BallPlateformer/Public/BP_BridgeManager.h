// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "BP_Beam.h"
#include "BP_Connector.h"
#include "BP_BridgeManager.generated.h"

UCLASS()
class BALLPLATEFORMER_API ABP_BridgeManager : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ABP_BridgeManager();

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Settings")
	TSubclassOf<ABP_Beam> BeamToSpawn;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Settings")
	TSubclassOf<ABP_Connector> ConnectorToSpawn;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Settings")
	USceneComponent* PointA;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Settings")
	USceneComponent* PointB;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Settings")
	int BeamAmount;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Settings")
	float AppliedForce;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Settings")
	float MinDistance;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Settings")
	float Stiffness;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Settings")
	float MaxStress;

public:
	UFUNCTION(CallInEditor, BlueprintCallable, category = "Settings")
	void GenerateBridge();
};