// Fill out your copyright notice in the Description page of Project Settings.

#include "BA_SlowZone.h"
#include "Components/BoxComponent.h"
#include "BA_Ball.h"

ABA_SlowZone::ABA_SlowZone()
{
	PrimaryActorTick.bCanEverTick = false;

	CollisionComponent = CreateDefaultSubobject<UBoxComponent>(TEXT("CollisionComponent"));
	CollisionComponent->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
	CollisionComponent->SetCollisionResponseToAllChannels(ECR_Ignore);
	CollisionComponent->SetCollisionResponseToChannel(ECC_Pawn, ECR_Overlap);
	CollisionComponent->SetGenerateOverlapEvents(true);
    
	RootComponent = CollisionComponent;

	CollisionComponent->OnComponentBeginOverlap.AddDynamic(this, &ABA_SlowZone::OnOverlapBegin);
	CollisionComponent->OnComponentEndOverlap.AddDynamic(this, &ABA_SlowZone::OnOverlapEnd);
}

void ABA_SlowZone::BeginPlay()
{
	Super::BeginPlay();
}

void ABA_SlowZone::OnOverlapBegin(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
							   UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep,
							   const FHitResult& SweepResult)
{
	ABA_Ball* Ball = Cast<ABA_Ball>(OtherActor);
	if (Ball)
	{
		Ball->SetSpeedMultiplier(SlowMultiplier);
	}
}

void ABA_SlowZone::OnOverlapEnd(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
							 UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	ABA_Ball* Ball = Cast<ABA_Ball>(OtherActor);
	if (Ball)
	{
		Ball->SetSpeedMultiplier(1.0f);
	}
}