// Fill out your copyright notice in the Description page of Project Settings.


#include "EnemyCharacterAnimInstance.h"

EEnemyStatus UEnemyCharacterAnimInstance::OnStatusAnimEnd()
{
	switch (EnemyStatus)
	{
	case EEnemyStatus::Locomotion:
		{
			if (hit)
				EnemyStatus = EEnemyStatus::Hit;
			else if (isAttacking)
				EnemyStatus = EEnemyStatus::Attack;
			break;
		}
	case EEnemyStatus::Hit:
		{
			if (dead)
				EnemyStatus = EEnemyStatus::Die;
			else 
				EnemyStatus = EEnemyStatus::Locomotion;
			break;
		}
	case EEnemyStatus::Attack:
		{
			isAttacking = false;
			EnemyStatus = EEnemyStatus::Locomotion;
			// 在 OnStatusAnimEnd 赋值后
			/*GEngine->AddOnScreenDebugMessage(-1, 2.f, FColor::Red, 
				FString::Printf(TEXT("动画实例状态已改为 Locomotion, 时间: %f"), GetWorld()->GetTimeSeconds()));*/
			break;
		}
	default:break;
	}
	return EnemyStatus;
}
