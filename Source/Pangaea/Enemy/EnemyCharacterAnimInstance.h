// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimInstance.h"
#include "EnemyCharacterAnimInstance.generated.h"

UENUM(BlueprintType)
enum class	EEnemyStatus :uint8
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
class PANGAEA_API UEnemyCharacterAnimInstance : public UAnimInstance
{
	GENERATED_BODY()
private:
	UPROPERTY(EditAnywhere, BlueprintReadWrite,Category="PlayerAnim", meta=(AllowPrivateAccess=true))
	float speed = 0;
	UPROPERTY(EditAnywhere, BlueprintReadWrite,Category="PlayerAnim", meta=(AllowPrivateAccess=true))
	bool dead = false;
	UPROPERTY(EditAnywhere, BlueprintReadWrite,Category="PlayerAnim", meta=(AllowPrivateAccess=true))
	bool isAttacking = false;
	UPROPERTY(EditAnywhere, BlueprintReadWrite,Category="PlayerAnim", meta=(AllowPrivateAccess=true))
	bool hit = false;
	UPROPERTY(VisibleAnywhere,BlueprintReadWrite, Category="PlayerAnim", meta=(AllowPrivateAccess=true,BluePrintProtected = true))
	EEnemyStatus EnemyStatus = EEnemyStatus::Locomotion;
public:
	UFUNCTION(BlueprintCallable)
	EEnemyStatus OnStatusAnimEnd();
	inline bool SetIsAttacking(bool value) 
	{
		isAttacking = value;
		return isAttacking;
	}
	inline bool GetIsAttacking() const
	{
		return isAttacking;
	}
	inline EEnemyStatus GetEnemyStatus() const
	{
		return EnemyStatus;
	}
};
