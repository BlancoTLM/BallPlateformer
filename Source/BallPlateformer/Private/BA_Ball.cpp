// Fill out your copyright notice in the Description page of Project Settings.

#include "BA_Ball.h"

#include "BA_PlayerController.h"
#include "BA_MoveingPlateform.h"
#include "GameFramework/PlayerController.h"
#include "Components/StaticMeshComponent.h"
#include "EnhancedInputSubsystems.h"
#include "EnhancedInputComponent.h"
#include "GameFramework/Controller.h"

ABA_Ball::ABA_Ball()
{
	PrimaryActorTick.bCanEverTick = true;

	BallMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("BallMesh"));
	RootComponent = BallMesh;
	BallMesh->SetSimulatePhysics(true);
	BallMesh->SetCollisionProfileName(TEXT("PhysicsActor"));
	BallMesh->SetMassOverrideInKg(NAME_None, 10.0f); // Ajuster si nécessaire
}

void ABA_Ball::BeginPlay()
{
	Super::BeginPlay();

	if (ABA_PlayerController* PC = Cast<ABA_PlayerController>(GetController()))
	{
		if (UEnhancedInputLocalPlayerSubsystem* InputSubsystem = 
			ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(PC->GetLocalPlayer()))
		{
			InputSubsystem->AddMappingContext(InputMapping, 0);
		}
	}
}

void ABA_Ball::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	CheckIfGrounded();
	
	if (OnMovingPlatform)
	{
		FVector NewLocation = GetActorLocation() + PlatformVelocity * DeltaTime;

		SetActorLocation(FVector(NewLocation.X, NewLocation.Y, GetActorLocation().Z), true);
	}

	if (BallMesh)
	{
		float MaxSpeed = SpeedMax * SpeedMultiplier;
		FVector Velocity = BallMesh->GetPhysicsLinearVelocity();

		if (Velocity.Size() > MaxSpeed)
		{
			FVector ClampedVelocity = Velocity.GetClampedToMaxSize(MaxSpeed);
			BallMesh->SetPhysicsLinearVelocity(ClampedVelocity);
		}

		if (BallMesh->IsSimulatingPhysics())
		{
			FVector GravityForce = GravityDirection * 980.0f * BallMesh->GetMass();
			BallMesh->AddForce(GravityForce, NAME_None, true);
		}
	}
}

void ABA_Ball::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	UEnhancedInputComponent* EnhancedInput = Cast<UEnhancedInputComponent>(PlayerInputComponent);
	if (EnhancedInput)
	{
		EnhancedInput->BindAction(MoveAction, ETriggerEvent::Triggered, this, &ABA_Ball::Move);
		EnhancedInput->BindAction(JumpAction, ETriggerEvent::Started, this, &ABA_Ball::Jump);
		EnhancedInput->BindAction(GravityAction, ETriggerEvent::Started, this, &ABA_Ball::ChangeGravity);
	}
}

void ABA_Ball::Move(const FInputActionValue& Value)
{
	FVector2D MovementVector = Value.Get<FVector2D>();
	FVector Force = FVector(MovementVector.X * MovementForce * SpeedMultiplier, MovementVector.Y * MovementForce * SpeedMultiplier, 0.0f);
	FVector Velocity = BallMesh->GetPhysicsLinearVelocity();
	BallMesh->AddForce(Force, NAME_None, false);
}

void ABA_Ball::Jump(const FInputActionValue& Value)
{
	if (IsGrounded || JumpCount < MaxJumps)
	{
		BallMesh->AddImpulse(FVector(0.0f, 0.0f, JumpImpulse), NAME_None, true);
		JumpCount++;
	}
}

void ABA_Ball::CheckIfGrounded()
{
	FVector Start = GetActorLocation();
	FVector End = Start - FVector(0.0f, 0.0f, 55.0f);

	FHitResult Hit;
	FCollisionQueryParams TraceParams;
	TraceParams.AddIgnoredActor(this);

	bool bHit = GetWorld()->LineTraceSingleByChannel(Hit, Start, End, ECC_Visibility, TraceParams);

	DrawDebugLine(GetWorld(), Start, End, bHit ? FColor::Green : FColor::Red, false, 0.1f, 0, 2.0f);

	IsGrounded = bHit;

	if (IsGrounded)
	{
		JumpCount = 0;

		ABA_MoveingPlateform* Platform = Cast<ABA_MoveingPlateform>(Hit.GetActor());
		if (Platform && Hit.Normal.Z > 0.7f)
		{
			OnMovingPlatform = true;
			PlatformVelocity = Platform->GetPlatformVelocity();
		}
	}
	else
	{
		OnMovingPlatform = false;
		PlatformVelocity = FVector::ZeroVector;
	}
}

void ABA_Ball::SetSpeedMultiplier(float Multiplier)
{
	SpeedMultiplier = Multiplier;
}

void ABA_Ball::SetGravityDirection(FVector NewGravity)
{
	GravityDirection = NewGravity.GetSafeNormal();
}

void ABA_Ball::ChangeGravity(const FInputActionValue& Value)
{
	GravityIsNormal = !GravityIsNormal;
	FVector NewGravity = FVector(0.0f, 0.0f, GravityIsNormal * SpeedMultiplier);
	SetGravityDirection(NewGravity);
}