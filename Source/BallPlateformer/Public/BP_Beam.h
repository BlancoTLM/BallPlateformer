// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "BP_Beam.generated.h"

class ABP_Connector;
UCLASS()
class BALLPLATEFORMER_API ABP_Beam : public AActor
{
	GENERATED_BODY()

public:	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Settings")
	UStaticMeshComponent* MeshComponent;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Settings")
	TArray<ABP_Connector*> Connectors;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Settings")
	UMaterialInterface* Material;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Settings")
	float MaxStress;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Settings")
	USceneComponent* TopLeft;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Settings")
	USceneComponent* TopRight;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Settings")
	USceneComponent* BotLeft;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Settings")
	USceneComponent* BotRight;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Settings")
	ABP_Connector* TopLeftConnector = nullptr;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Settings")
	ABP_Connector* TopRightConnector = nullptr;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Settings")
	ABP_Connector* BotLeftConnector = nullptr;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Settings")
	ABP_Connector* BotRightConnector = nullptr;

private:
	UMaterialInstanceDynamic* DynamicMaterial;
	float Timer;
	
public:	
	ABP_Beam();

	virtual void Tick(float DeltaTime) override;
	virtual void BeginPlay() override;
	FVector GetCornerPosition(const ABP_Connector* Connector);
	void ConnectConnectors();
};