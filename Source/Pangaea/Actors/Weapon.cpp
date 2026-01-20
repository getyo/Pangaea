// Fill out your copyright notice in the Description page of Project Settings.


#include "Weapon.h"
#include "Pangaea/Interface/DamagableInterface.h"
#include "Pangaea/Character/Player//PlayerCharacter.h"

// Sets default values
AWeapon::AWeapon() : _HitCountDown(0)
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	StaticMesh = CreateDefaultSubobject<UStaticMeshComponent>("StaticMesh");
	SetRootComponent(StaticMesh);
	StaticMesh->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
	StaticMesh->SetCollisionObjectType(ECC_WorldDynamic);
	StaticMesh->SetCollisionProfileName(TEXT("OverlapOnlyPawn"));
	
	OnActorBeginOverlap.AddDynamic(this,&AWeapon::OnWeaponOverlapBegin);
}

// Called when the game starts or when spawned
void AWeapon::BeginPlay()
{
	Super::BeginPlay();
}

// Called every frame
void AWeapon::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	if (_HitCountDown >= 0)
		_HitCountDown -= DeltaTime;
	if (!_Holder)
	{
		//没有持有者自旋转，每秒300°
		FQuat RotQuat = FQuat(FRotator(0.0f, 300.f * DeltaTime, 0.0f));
		AddActorLocalRotation(RotQuat);
	}
}

void AWeapon::OnWeaponOverlapBegin(AActor* OverlappedActor, AActor* OtherActor)
{
	if (_Holder)
	{
		//打到人，且打到的不是自己
		if (OtherActor == _Holder) return;
		auto HitActor = Cast<IDamagableInterface>(OtherActor);
		if (!HitActor) return;
		
		//当前正在攻击状态
		auto HolderAnim = Cast<UGeneralCharacterAnimInstance>(_Holder->GetMesh()->GetAnimInstance());
		if (!HolderAnim) return;
		if (!HolderAnim->GetIsAttacking() || _HitCountDown > 0) return;

		HitActor->Hurt(Strength+_Holder->Strength,_Holder->Camp);
		_HitCountDown = HitSpan;
		return;
	}
		
	auto Player = Cast<APlayerCharacter>(OtherActor);
	if (!Player)
		return;
	
	//拆卸当前武器
	TArray<AActor*> AttachedActors;
	Player->GetAttachedActors(AttachedActors);
	//因为只有一个武器Actor挂载在玩家上，所以这个循环实际只执行一次
	for (AActor* Actor : AttachedActors)
	{
		auto * AttachedWeapon = Cast<AWeapon>(Actor);
		if (AttachedWeapon)
		{
			Actor->DetachFromActor(FDetachmentTransformRules::KeepWorldTransform);
			Actor->SetActorRotation(FQuat::Identity);
			AttachedWeapon->Owner = nullptr;
		}
	}
	
	this->_Holder = Player;
	FAttachmentTransformRules AttachmentRules(EAttachmentRule::SnapToTarget, true);
	this->AttachToComponent(Player->GetMesh(), AttachmentRules,FName("rhand_weapon"));
	Player->SetWeapon(this);
}

