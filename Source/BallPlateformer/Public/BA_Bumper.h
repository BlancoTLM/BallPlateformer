// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "BA_Bumper.generated.h"

UCLASS()
class BALLPLATEFORMER_API ABA_Bumper : public AActor
{
	GENERATED_BODY()
	
public:	
	ABA_Bumper();

protected:
	virtual void BeginPlay() override;

public:	
	virtual void Tick(float DeltaTime) override;

	UPROPERTY(VisibleAnywhere)
	class UCapsuleComponent* CollisionComponent;

	UPROPERTY(EditAnywhere, Category = "Settings")
	float ImpulseStrength = 1000.0f;

	UFUNCTION()
	void OnHitBegin(class UPrimitiveComponent* OverlappedComponent, class AActor* OtherActor, 
						class UPrimitiveComponent* OtherComp, FVector NormalImpulse, 
						const FHitResult& SweepResult);
};