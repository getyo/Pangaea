// Fill out your copyright notice in the Description page of Project Settings.


#include "ADefenseTower.h"
#include "Kismet/KismetMathLibrary.h"
#include "Projectile.h"
#include "Components/SphereComponent.h"
#include "Net/UnrealNetwork.h"

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
	bReplicates = true;
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
	_HealthPoints = MaxHealthPoints;
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

void ADefenseTower::GetLifetimeReplicatedProps(TArray<class FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);
	DOREPLIFETIME(ADefenseTower, _HealthPoints);
}

void ADefenseTower::OnRep_HealthPoints()
{
	if (_HealthPoints <= 0) 
		DestroyProcess();
}

void ADefenseTower::FireBallSpawn_BroadCast_RPC_Implementation()
{
	AProjectile * Projectile = GetProjectile(_FireBallClass,this);
	if (!Projectile)
	{
		GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red,
			FString::Printf(TEXT("Class %s, Cannot Spawn %s's Actor"),
				*GetName(), *_FireBallClass->GetName()));
		return;
	}
	
	auto StartLocation = this->GetActorLocation();
	auto EndLocation = _TargetPlayer->GetActorLocation();
	StartLocation.Z += 100.f;
	auto LookAtRotation = UKismetMathLibrary::FindLookAtRotation(StartLocation, EndLocation);
	Projectile->SetActorLocation(StartLocation);
	
	Projectile->GetProjectileMovementComponent()->Velocity = LookAtRotation.Vector() * Projectile->GetProjectileMovementComponent()->InitialSpeed;
	Projectile->GetProjectileMovementComponent()->UpdateComponentVelocity();
	//本地关闭碰撞
	if (!HasAuthority())
		Projectile->SetActorEnableCollision(false);
}

void ADefenseTower::Fire()
{
	if (!HasAuthority()) return;
	FireBallSpawn_BroadCast_RPC();
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

AProjectile* ADefenseTower::GetProjectile(UClass* ProjectClass, const UObject* Context)
{
	if (ProjectClass == nullptr) return nullptr;
	AProjectile * Projectile = nullptr;
	if (!_ProjectPool.Dequeue(Projectile))
	{
	
			Projectile = Cast<AProjectile>(Context->GetWorld()->SpawnActor(ProjectClass));
			Projectile->_Holder = this;
			Projectile->Camp = Camp;
	}
	Projectile->StartProjectile();
	return Projectile;
}

void ADefenseTower::RecycleProjectile(AProjectile* Projectile)
{
	if (Projectile == nullptr) return;
	_ProjectPool.Enqueue(Projectile);
	Projectile->ResetProjectile();
}

void ADefenseTower::Hurt(float Damage, E_Camp SourceCamp)
{
	if (SourceCamp == Camp) return;
	if (HasAuthority())
	{
		_HealthPoints -= Damage;
		FTimerHandle TimerHandle;
		if (_HealthPoints <= 0)
		{
			GetWorldTimerManager().SetTimer(TimerHandle, [this]()
			{			
				// 在执行逻辑前，先检查自己是否还活着
				if (this && IsValid(this)) 
				{
					this->DestroyProcess();
				}
			}, 0.2f, false);
		}
	}
}

void ADefenseTower::DestroyProcess_Implementation()
{
	AProjectile * Projectile = nullptr;
	while (_ProjectPool.Dequeue(Projectile))
	{
		Projectile->Destroy();
	}
	Super::Destroy();
}

