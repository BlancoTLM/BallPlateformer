// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "EnhancedInputSubsystems.h"
#include "EnhancedInputComponent.h"
#include "BA_Ball.generated.h"

UCLASS()
class BALLPLATEFORMER_API ABA_Ball : public APawn
{
	GENERATED_BODY()

public:
	ABA_Ball();

protected:

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Settings")
	float MovementForce = 100000.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Settings")
	float JumpImpulse = 500000.0f;

	int JumpCount = 0;
	int MaxJumps = 1;

	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;
	virtual void CheckIfGrounded();

public:
	void SetSpeedMultiplier(float Multiplier);
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Settings")
	float SpeedMax = 300.0f;
	
private:
	float SpeedMultiplier = 1.0f;
	bool OnMovingPlatform = false;
	bool GravityIsNormal = true;
	FVector PlatformVelocity;
	FVector GravityDirection = FVector(0.0f, 0.0f, -1.0f);

public:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Settings")
	class UStaticMeshComponent* BallMesh;

	UPROPERTY(EditAnywhere, Category = "Settings")
	class UInputMappingContext* InputMapping;

	UPROPERTY(EditAnywhere, Category = "Settings")
	class UInputAction* MoveAction;

	UPROPERTY(EditAnywhere, Category = "Settings")
	class UInputAction* JumpAction;

	UPROPERTY(EditAnywhere, Category = "Settings")
	class UInputAction* GravityAction;

	bool IsGrounded = false;

	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
	void Move(const FInputActionValue& Value);
	void Jump(const FInputActionValue& Value);
	void SetGravityDirection(FVector NewGravity);
	void ChangeGravity(const FInputActionValue& Value);
};
