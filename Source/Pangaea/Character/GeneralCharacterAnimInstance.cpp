// Fill out your copyright notice in the Description page of Project Settings.


#include "GeneralCharacterAnimInstance.h"

CharacterStatus UGeneralCharacterAnimInstance::OnStatusAnimEnd()
{
	switch (Status)
	{
	case CharacterStatus::Locomotion:
		{
			if (dead)
				Status = CharacterStatus::Die;
			else if (hit)
				Status = CharacterStatus::Hit;
			else if (isAttacking)
				Status = CharacterStatus::Attack;
			break;
		}
	case CharacterStatus::Hit:
		{
			if (dead)
				Status = CharacterStatus::Die;
			else if (isAttacking)
			{
				isAttacking = false;
			}
			else if (hit)
			{
				hit = false;
				Status = CharacterStatus::Locomotion;
			}
			break;
		}
	case CharacterStatus::Attack:
		{
			if (dead)
				Status = CharacterStatus::Die;
			else if (hit)
			{
				hit = false;
			}
			else if (isAttacking)
			{
				isAttacking = false;
				Status = CharacterStatus::Locomotion;
			}
			// 在 OnStatusAnimEnd 赋值后
			/*GEngine->AddOnScreenDebugMessage(-1, 2.f, FColor::Red, 
				FString::Printf(TEXT("动画实例状态已改为 Locomotion, 时间: %f"), GetWorld()->GetTimeSeconds()));*/
			break;
		}
	case CharacterStatus::Die:
		{
			if (dead)
			{
				Status = CharacterStatus::Die;
			}
			break;
		}
	default:break;
	}
	/*const UEnum * EnumClass = StaticEnum<CharacterStatus>();
	GEngine->AddOnScreenDebugMessage(-1,20.f,FColor::Green,
		FString::Printf(TEXT("Character Class : %s,Currnet Status%s"),
			*TryGetPawnOwner()->GetClass()->GetName(), *EnumClass->GetNameByValue(static_cast<int>(Status)).ToString()));*/
	return Status;
}
