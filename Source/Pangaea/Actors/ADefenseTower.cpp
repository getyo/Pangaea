// Fill out your copyright notice in the Description page of Project Settings.


#include "ADefenseTower.h"

// Sets default values
ADefenseTower::ADefenseTower()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	_BoxComponent = CreateDefaultSubobject<UBoxComponent>(TEXT("Box Collision"));
	SetRootComponent(_BoxComponent);
	_StaticMeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Static Mesh"));
	_StaticMeshComponent->SetupAttachment(_BoxComponent);
}

// Called when the game starts or when spawned
void ADefenseTower::BeginPlay()
{
	Super::BeginPlay();
	
}

int ADefenseTower::GetHealthPoints() {
	return _HealthPoints;
}

bool ADefenseTower::CanFire() {
	return _ReloadCountingDown <= 0;
}

bool ADefenseTower::IsDestoryed() {
	return _HealthPoints <= 0;
}

// Called every frame
void ADefenseTower::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

