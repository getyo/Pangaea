// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerAvatarAnimInstance.h"

//就实际情况来讲，你最好的做法还是那种动作打断系统，但是现在只是一个示例
//没必要那么复杂
EPlayerStatus UPlayerAvatarAnimInstance::OnStatusAnimEnd()
{
	switch (playerStatus)
	{
	case EPlayerStatus::Locomotion:
		{
			if (hit)
				playerStatus = EPlayerStatus::Hit;
			else if (isAttacking)
				playerStatus = EPlayerStatus::Attack;
			break;
		}
	case EPlayerStatus::Hit:
		{
			if (dead)
				playerStatus = EPlayerStatus::Die;
			else 
				playerStatus = EPlayerStatus::Locomotion;
			break;
		}
	case EPlayerStatus::Attack:
		{
			isAttacking = false;
			playerStatus = EPlayerStatus::Locomotion;
			break;
		}
	default:break;
	}
	return playerStatus;
}
