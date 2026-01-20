// Fill out your copyright notice in the Description page of Project Settings.


#include "Projectile.h"

// Sets default values
AProjectile::AProjectile():_LifeCountingDown(LifeSpan)
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	MeshComp = CreateDefaultSubobject<UStaticMeshComponent>("MeshComp");
	SetRootComponent(MeshComp);
	ProjectileMovementComponent = CreateDefaultSubobject<UProjectileMovementComponent>("ProjectileMovementComponent");
	ProjectileMovementComponent->SetUpdatedComponent(MeshComp);
	OnActorBeginOverlap.AddDynamic(this, &AProjectile::OnOverlapBegin);
}

// Called when the game starts or when spawned
void AProjectile::BeginPlay()
{
	Super::BeginPlay();
	ProjectileMovementComponent->InitialSpeed = Speed;
	ProjectileMovementComponent->MaxSpeed = Speed;
	ProjectileMovementComponent->ProjectileGravityScale = 0;
}

// Called every frame
void AProjectile::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	_LifeCountingDown-= DeltaTime;
	if (_LifeCountingDown <= 0.0f)
	{
		if (_Holder) _Holder->RecycleProjectile(this);
	}
	
}

void AProjectile::ResetProjectile()
{
	SetActorHiddenInGame(true);
	SetActorTickEnabled(false);
}

void AProjectile::StartProjectile()
{
	SetActorHiddenInGame(false);
	SetActorTickEnabled(true);
	this->_LifeCountingDown = LifeSpan;
}

void AProjectile::OnOverlapBegin(AActor* OverlappedActor, AActor* OtherActor)
{
	auto HitActor = Cast<IDamagableInterface> (OtherActor);
	if (!HitActor ) return;
	HitActor->Hurt(Damage,Camp);
}














