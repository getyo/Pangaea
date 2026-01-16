// Fill out your copyright notice in the Description page of Project Settings.


#include "ADefenseTower.h"
#include "Kismet/KismetMathLibrary.h"
#include "Projectile.h"
#include "Components/SphereComponent.h"

// Sets default values
ADefenseTower::ADefenseTower()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	SphereComponent = CreateDefaultSubobject<USphereComponent>(TEXT("Sphere Collision"));
	SetRootComponent(SphereComponent);
	SphereComponent->SetSphereRadius(500.f);
	SphereComponent->OnComponentBeginOverlap.AddDynamic(this,&ADefenseTower::OnSphereOverlapBegin);
	SphereComponent->OnComponentEndOverlap.AddDynamic(this,&ADefenseTower::OnSphereOverlapEnd);
	
	StaticMeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Static Mesh"));
	StaticMeshComponent->SetupAttachment(SphereComponent);
	
	static ConstructorHelpers::FClassFinder<AActor> FireBallClassFinder(TEXT("/Game/TopDown/Blueprints/Actor/BP_FireBall.BP_FireBall_C"));
	
	if (FireBallClassFinder.Succeeded())
	{
		_FireBallClass = FireBallClassFinder.Class;
	}
	else
	{
		UE_LOG(LogTemp, Error, TEXT("Class: %s,Class Failed to find FireBall Class!"),*GetName());
	}
}

// Called when the game starts or when spawned
void ADefenseTower::BeginPlay()
{
	Super::BeginPlay();
	SetActorTickInterval(0.5f);
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
	if (_ReloadCountingDown > 0)
		_ReloadCountingDown -= DeltaTime;
	if (_TargetPlayer && CanFire())
	{
		Fire();
		_ReloadCountingDown = ReloadInterval;
	}
}

void ADefenseTower::Fire()
{
	AProjectile * Projectile = Cast<AProjectile>(GetWorld()->SpawnActor(_FireBallClass));
	if (!Projectile)
	{
		GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Yellow,
			FString::Printf(TEXT("Class %s, Cannot Spawn %s's Actor"),
				*GetName(), *_FireBallClass->GetName()));
	}
	
	auto StartLocation = this->GetActorLocation();
	auto EndLocation = _TargetPlayer->GetActorLocation();
	StartLocation.Z += 100.f;
	auto LookAtRotation = UKismetMathLibrary::FindLookAtRotation(StartLocation, EndLocation);
	Projectile->SetActorLocation(StartLocation);
	
	Projectile->GetProjectileMovementComponent()->Velocity = LookAtRotation.Vector() * Projectile->GetProjectileMovementComponent()->InitialSpeed;
	Projectile->GetProjectileMovementComponent()->UpdateComponentVelocity();
}

void ADefenseTower::OnSphereOverlapBegin(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	auto Player = Cast<APlayerCharacter>(OtherActor);
	if (!Player)	return;
	_TargetPlayer = Player;
}

void ADefenseTower::OnSphereOverlapEnd(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int OtherBodyIndex)
{
	auto Player = Cast<APlayerCharacter>(OtherActor);
	if (!Player || !_TargetPlayer)	return;
	_TargetPlayer = nullptr;
}
