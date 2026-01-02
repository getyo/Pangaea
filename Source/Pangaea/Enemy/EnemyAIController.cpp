// Fill out your copyright notice in the Description page of Project Settings.


#include "EnemyAIController.h"

#include "EnemyCharacter.h"

void AEnemyAIController::MakeAttackDecsion(APawn* Target)
{
	auto EnemyCharacter = Cast<AEnemyCharacter>(GetPawn());
	if (EnemyCharacter && EnemyCharacter->GetDistanceTo(Target) <= EnemyCharacter->AttackRange)
	{
		if (EnemyCharacter->CanAttack())
			EnemyCharacter->Attack();
	}
}
