// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Perception/PawnSensingComponent.h"
#include "EnemyCharacter.generated.h"

UCLASS()
class PANGAEA_API AEnemyCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AEnemyCharacter();
	
	UPROPERTY(EditAnywhere, Category = "EnemyCharacter")
	int HealthPoints = 500;
	UPROPERTY(EditAnywhere, Category = "EnemyCharacter")
	float Strength = 10;
	UPROPERTY(EditAnywhere, Category = "EnemyCharacter")
	float Armer = 3;
	UPROPERTY(EditAnywhere, Category = "EnemyCharacter")
	float AttackRange = 200;
	UPROPERTY(EditAnywhere, Category = "EnemyCharacter")
	float AttackInterval = 2;
	UPROPERTY(EditAnywhere, Category = "EnemyCharacter")
	float ChaseRange = 3000;

	UFUNCTION(BlueprintPure, Category = "EnemyCharacter")
	inline int GetHealthPoints() const
	{
		return _HealthPoints;
	}
	UFUNCTION(BlueprintPure, Category = "EnemyCharacter")
	inline bool IsKilled() const
	{
		return _HealthPoints <= 0;
	}
	UFUNCTION(BlueprintCallable, Category = "EnemyCharacter")
	bool CanAttack();
	void Attack();
	void Hit(int damage);
	
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	int _HealthPoints;
	float _AttackCountingDown;
	APawn * _ChasedTarget = nullptr;
	UPROPERTY(VisibleAnywhere,BlueprintReadOnly,Category="EnemyCharacter")
	UPawnSensingComponent * PawnSensingComponent = nullptr;
	
private:	
	//用于重置_ChaseTarget的值，因为PawnSensingComponent并不会说自己看不见了
	FTimerHandle TargetLostTimerHandle;
	inline  void ClearTarget()
	{
		_ChasedTarget = nullptr;
	}
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	UFUNCTION()
	void ChaseTarget(APawn* SeenPawn);

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
	UFUNCTION(BlueprintCallable, Category = "EnemyCharacter",meta=(AllowPrivateAccess=true))
	void DieProcess()
	{
		Destroy();
	}

};
