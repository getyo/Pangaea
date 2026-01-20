// Fill out your copyright notice in the Description page of Project Settings.


#include "GeneralCharacter.h"

// Sets default values
AGeneralCharacter::AGeneralCharacter():_CurHealthPoints(MaxHealthPoints),_AttackCountingDown(0)
{
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

// Called every frame
void AGeneralCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	if (_AttackCountingDown >= 0)
	{
		_AttackCountingDown -= DeltaTime;
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

void AGeneralCharacter::Attack()
{
	if (CanAttack())
	{
		_AttackCountingDown = AttackInterval;

		if (_AnimInstance)
			_AnimInstance->SetIsAttacking(true);
	}
}

void AGeneralCharacter::Hurt(float Damage,E_Camp SourceCamp)
{
	if (SourceCamp == Camp) return;
	_CurHealthPoints -= Damage;
	if (_CurHealthPoints <= 0)
		_AnimInstance->SetDead(true);
	else if (!_AnimInstance->GetHit())
		_AnimInstance->SetHit(true);
}
