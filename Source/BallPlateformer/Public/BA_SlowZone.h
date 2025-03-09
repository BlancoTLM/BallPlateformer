// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "BA_SlowZone.generated.h"

class UBoxComponent;
class ABallCharacter;

UCLASS()
class BALLPLATEFORMER_API ABA_SlowZone : public AActor
{
	GENERATED_BODY()
	
public:	
	ABA_SlowZone();

protected:
	virtual void BeginPlay() override;

public:
	UPROPERTY(VisibleAnywhere, Category = "Settings")
	UBoxComponent* CollisionComponent;

	UPROPERTY(EditAnywhere, Category = "Settings")
	float SlowMultiplier = 0.5f;

	UFUNCTION()
	void OnOverlapBegin(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
						UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep,
						const FHitResult& SweepResult);

	UFUNCTION()
	void OnOverlapEnd(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
					  UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);

};