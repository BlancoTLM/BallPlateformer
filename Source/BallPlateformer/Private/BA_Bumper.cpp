// Fill out your copyright notice in the Description page of Project Settings.

#include "BA_Bumper.h"
#include "Components/CapsuleComponent.h"
#include "GameFramework/Actor.h"
#include "BA_Ball.h"

ABA_Bumper::ABA_Bumper()
{
	PrimaryActorTick.bCanEverTick = true;

	RootComponent = CollisionComponent;

	CollisionComponent = CreateDefaultSubobject<UCapsuleComponent>(TEXT("CollisionComponent"));
	CollisionComponent->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
	CollisionComponent->SetCollisionResponseToAllChannels(ECR_Block);
	CollisionComponent->OnComponentHit.AddDynamic(this, &ABA_Bumper::OnHitBegin);
}

void ABA_Bumper::BeginPlay()
{
	Super::BeginPlay();
}

void ABA_Bumper::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void ABA_Bumper::OnHitBegin(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit)
{
	if (ABA_Ball* Ball = Cast<ABA_Ball>(OtherActor))
	{
		
		FVector ImpulseDirection = (Ball->GetActorLocation() - GetActorLocation()).GetSafeNormal();
		Ball->BallMesh->AddImpulse(ImpulseDirection * ImpulseStrength);
	}
}