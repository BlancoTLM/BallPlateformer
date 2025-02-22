// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "BA_Ball.generated.h"


UCLASS()
class BALLPLATEFORMER_API ABA_Ball : public APawn
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	ABA_Ball();

protected:
	// Composant de la sphère
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Settings")
	class UStaticMeshComponent* BallMesh;

	// Force appliquée pour le mouvement
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Settings")
	float MovementForce = 100000.0f;

	// Force appliquée pour le saut
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Settings")
	float JumpImpulse = 500000.0f;

	// Nombre de sauts
	int JumpCount = 0;
	int MaxJumps = 1;

	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;
	virtual void CheckIfGrounded();

public:
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	// Fonctions de mouvement
	void Move(const FInputActionValue& Value);
	void Jump(const FInputActionValue& Value);

	// Mapping Context pour Enhanced Input
	UPROPERTY(EditAnywhere, Category = "Settings")
	class UInputMappingContext* InputMapping;

	// Actions pour le déplacement et le saut
	UPROPERTY(EditAnywhere, Category = "Settings")
	class UInputAction* MoveAction;

	UPROPERTY(EditAnywhere, Category = "Settings")
	class UInputAction* JumpAction;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Settings")
	bool bIsGrounded = false;
};
