// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "GeneralCharacterAnimInstance.h"
#include "Pangaea/Interface/DamagableInterface.h"
#include "GeneralCharacter.generated.h"

UCLASS()
class PANGAEA_API AGeneralCharacter : public ACharacter,public IDamagableInterface
{
	GENERATED_BODY()

public:
	AGeneralCharacter();
	UPROPERTY(EditAnywhere, Category = "EnemyCharacter")
	int MaxHealthPoints = 30;
	UPROPERTY(EditAnywhere, Category = "EnemyCharacter")
	float Strength = 10;
	UPROPERTY(EditAnywhere, Category = "EnemyCharacter")
	float AttackInterval = 2;
	UPROPERTY(EditAnywhere, BlueprintReadWrite,Category = "EnemyCharacter")
	E_Camp Camp;
	
	
	UFUNCTION(BlueprintPure, Category = "EnemyCharacter")
	inline int GetHealthPoints() const
	{
		return _CurHealthPoints;
	}
	UFUNCTION(BlueprintPure, Category = "EnemyCharacter")
	inline bool IsKilled() const
	{
		return _CurHealthPoints <= 0;
	}
	UFUNCTION(BlueprintCallable, Category = "EnemyCharacter")
	virtual bool CanAttack();
	void Attack();
	virtual void Hurt(float Damage,E_Camp SourceCamp) override;
	
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	int _CurHealthPoints;
	float _AttackCountingDown;
	UGeneralCharacterAnimInstance* _AnimInstance;
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
	UFUNCTION(BlueprintCallable, Category = "EnemyCharacter",meta=(AllowPrivateAccess=true))
	virtual void DieProcess()
	{
		Destroy();
	}
private:	


};
