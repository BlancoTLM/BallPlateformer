// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "BP_Beam.h"
#include "BP_Connector.generated.h"

UCLASS()
class BALLPLATEFORMER_API ABP_Connector : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ABP_Connector();

	virtual void Tick(float DeltaTime) override;
	virtual void BeginPlay() override;
	UStaticMeshComponent* MeshComponent;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Settings")
	TArray<ABP_Beam*> ConnectedBeams;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Settings")
	float AppliedForce;
};