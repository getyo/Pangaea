// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimInstance.h"
#include "GeneralCharacterAnimInstance.generated.h"
UENUM(BlueprintType)
enum class	CharacterStatus :uint8
{
	Locomotion,
	Attack,
	Hit,
	Die
};
/**
 * 
 */
UCLASS()
class PANGAEA_API UGeneralCharacterAnimInstance : public UAnimInstance
{
	GENERATED_BODY()
private:
	UE::FRecursiveMutex StatusModifyLock;
	UPROPERTY(EditAnywhere, BlueprintReadWrite,Category="CharacterAnim", meta=(AllowPrivateAccess=true))
	float speed = 0;
	UPROPERTY(EditAnywhere, BlueprintReadWrite,Category="CharacterAnim", meta=(AllowPrivateAccess=true))
	bool dead = false;
	UPROPERTY(VisibleAnywhere,BlueprintReadOnly,Category="CharacterAnim", meta=(AllowPrivateAccess=true))
	bool isAttacking = false;
	UPROPERTY(EditAnywhere, BlueprintReadWrite,Category="CharacterAnim", meta=(AllowPrivateAccess=true))
	bool hit = false;
	UPROPERTY(VisibleAnywhere,BlueprintReadWrite, Category="CharacterAnim", meta=(AllowPrivateAccess=true,BluePrintProtected = true))
	CharacterStatus Status = CharacterStatus::Locomotion;
public:
	UFUNCTION(BlueprintCallable)
	CharacterStatus OnStatusAnimEnd();
	inline void SetIsAttacking(bool value) 
	{
		StatusModifyLock.Lock();
		isAttacking = value;
		OnStatusAnimEnd();
	}
	inline bool GetIsAttacking() const
	{
		return isAttacking;
	}
	inline void SetHit(bool val)
	{
		StatusModifyLock.Lock();
		hit = val;
		OnStatusAnimEnd();
	}
	inline bool GetHit() const
	{
		return hit;
	}
	inline void SetDead(bool value)
	{
		StatusModifyLock.Lock();
		dead = value;
		OnStatusAnimEnd();
	}
	inline bool GetDead() const
	{
		return dead;
	}
	inline CharacterStatus GetCharacterAnimStatus() const
	{
		return Status;
	}
	
};
