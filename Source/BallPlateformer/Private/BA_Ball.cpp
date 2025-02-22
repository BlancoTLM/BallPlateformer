// Fill out your copyright notice in the Description page of Project Settings.

#include "BA_Ball.h"

#include "BA_PlayerController.h"
#include "GameFramework/PlayerController.h"
#include "Components/StaticMeshComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "GameFramework/Controller.h"
#include "Camera/CameraComponent.h"

// Sets default values
ABA_Ball::ABA_Ball()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	// Création du composant de la sphère
	BallMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("BallMesh"));
	RootComponent = BallMesh;

	// Activer la physique
	BallMesh->SetSimulatePhysics(true);
	BallMesh->SetCollisionProfileName(TEXT("PhysicsActor"));
	BallMesh->SetMassOverrideInKg(NAME_None, 10.0f); // Ajuster si nécessaire
}

// Called when the game starts or when spawned
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
}

void ABA_Ball::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	UEnhancedInputComponent* EnhancedInput = Cast<UEnhancedInputComponent>(PlayerInputComponent);
	if (EnhancedInput)
	{
		EnhancedInput->BindAction(MoveAction, ETriggerEvent::Triggered, this, &ABA_Ball::Move);
		EnhancedInput->BindAction(JumpAction, ETriggerEvent::Started, this, &ABA_Ball::Jump);
	}
}

void ABA_Ball::Move(const FInputActionValue& Value)
{
	FVector2D MovementVector = Value.Get<FVector2D>();
	FVector Force = FVector(MovementVector.X * MovementForce, MovementVector.Y * MovementForce, 0.0f);
	BallMesh->AddForce(Force, NAME_None, false);
}

void ABA_Ball::Jump(const FInputActionValue& Value)
{
	bool bIsPressed = Value.Get<bool>();
	
	if (bIsPressed && (bIsGrounded || JumpCount < MaxJumps))
	{
		BallMesh->AddImpulse(FVector(0.0f, 0.0f, JumpImpulse), NAME_None, true);
		JumpCount++;
	}
}

void ABA_Ball::CheckIfGrounded()
{
	FVector Start = GetActorLocation();
	FVector End = Start - FVector(0.0f, 0.0f, 55.0f); // 55 = Rayon de la sphère + marge de sécurité

	FHitResult Hit;
	FCollisionQueryParams TraceParams;
	TraceParams.AddIgnoredActor(this); // Ne pas se détecter soi-même

	// Lancer le RayTrace
	bool bHit = GetWorld()->LineTraceSingleByChannel(Hit, Start, End, ECC_Visibility, TraceParams);

	// Debug : Dessiner le rayon dans l’éditeur
	DrawDebugLine(GetWorld(), Start, End, bHit ? FColor::Green : FColor::Red, false, 0.1f, 0, 2.0f);

	// Mettre à jour la variable
	bIsGrounded = bHit;
}
