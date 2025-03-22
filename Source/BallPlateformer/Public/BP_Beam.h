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
	// Sets default values for this actor's properties
	ABP_Beam();

	virtual void Tick(float DeltaTime) override;
	virtual void BeginPlay() override;
	UStaticMeshComponent* MeshComponent;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Settings")
	TArray<ABP_Connector*> Connectors;
};