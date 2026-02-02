// Fill out your copyright notice in the Description page of Project Settings.


#include "GeneralCharacter.h"
#include "Pangaea/Actors/Weapon.h"
#include "Enemy/EnemyCharacter.h"
#include "Net/UnrealNetwork.h"

// Sets default values
AGeneralCharacter::AGeneralCharacter():_CurHealthPoints(MaxHealthPoints),_AttackCountingDown(0),_HitCountingDown(0)
{
	bReplicates = true;
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AGeneralCharacter::BeginPlay()
{
	Super::BeginPlay();
	_AnimInstance = Cast<UGeneralCharacterAnimInstance>(GetMesh()->GetAnimInstance());
	_CurHealthPoints = MaxHealthPoints;
}

void AGeneralCharacter::GetLifetimeReplicatedProps(TArray<class FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);
	DOREPLIFETIME(AGeneralCharacter,_CurHealthPoints);
	DOREPLIFETIME(AGeneralCharacter,_Weapon);
}

// Called every frame
void AGeneralCharacter::Tick(float DeltaTime){
	Super::Tick(DeltaTime);
	if (_AttackCountingDown >= 0)
	{
		_AttackCountingDown -= DeltaTime;
	}
	if (_HitCountingDown >= 0)
	{
		_HitCountingDown -= DeltaTime;
	}
}

// Called to bind functionality to input
void AGeneralCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}



bool AGeneralCharacter::CanAttack() {
	return _AttackCountingDown <= 0;
}

bool AGeneralCharacter::CanHit()
{
	return _HitCountingDown <= 0;
}


void AGeneralCharacter::Attack()
{
	if (CanAttack())
	{
		_AttackCountingDown = AttackInterval;

		if (_AnimInstance)
		{
			_AnimInstance->SetIsAttacking(true);
		}
	}
}

void AGeneralCharacter::AttackC_RPC_Implementation()
{
	AttackS_BroadCast_RPC();
}

void AGeneralCharacter::AttackS_BroadCast_RPC_Implementation()
{
	Attack();	
}

void AGeneralCharacter::Hurt(float Damage,E_Camp SourceCamp)
{
	if (SourceCamp == Camp) return;
	if (!HasAuthority()) return;
	if (this->IsA<AEnemyCharacter>())
	{
		GEngine->AddOnScreenDebugMessage(-1,20.f,FColor::Green,
			FString::Printf(TEXT("Hurt Damage : %f,Health :%f"),Damage,_CurHealthPoints));
	}
	_CurHealthPoints -= Damage;
	//服务器方面不会触发这个事件，需要手动调用
	OnRepCurHealthPoints();
}

void AGeneralCharacter::DieProcess_Implementation()
{
	if (_Weapon)
	{
		_Weapon->Destroy();
		_Weapon = nullptr;
	}
	Destroy();
}

void AGeneralCharacter::OnRepCurHealthPoints_Implementation()
{
	if (!_AnimInstance) return;
	if (_CurHealthPoints <= 0)
	{
		_AnimInstance->SetDead(true);
	}
	else if (!_AnimInstance->GetHit() && CanHit())
	{
		_AnimInstance->SetHit(true);
		_HitCountingDown = _HitInterval;
	}
}

void AGeneralCharacter::OnRep_Weapon()
{
	if (_Weapon)
		_Weapon->SetHolder(this);
}

void AGeneralCharacter::RequestDamageToServer_Implementation(float Damage, E_Camp SourceCamp, AActor* Target)
{
	auto HitActor = Cast<IDamageableInterface>(Target);
	if (HitActor)
		HitActor->Hurt(Damage,SourceCamp);
}










