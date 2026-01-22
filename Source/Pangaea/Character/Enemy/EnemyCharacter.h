// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Perception/PawnSensingComponent.h"
#include "Pangaea/Character/GeneralCharacter.h"
#include "Pangaea/Actors/Weapon.h"
#include "EnemyCharacter.generated.h"

UCLASS(Blueprintable,BlueprintType)
class PANGAEA_API AEnemyCharacter : public AGeneralCharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AEnemyCharacter();
	virtual bool CanAttack() override;
	
	UPROPERTY(EditAnywhere, Category = "EnemyCharacter")
	float ChaseRange = 3000;
	UPROPERTY(EditAnywhere, Category = "EnemyCharacter")
	float AttackRange = 200;

	
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	APawn * _ChasedTarget = nullptr;
	UClass * _WeaponClass = nullptr;
	UPROPERTY(ReplicatedUsing=OnRep_Weapon)
	AWeapon * _Weapon = nullptr;
	UPROPERTY(VisibleAnywhere,BlueprintReadOnly,Category="EnemyCharacter")
	UPawnSensingComponent * PawnSensingComponent = nullptr;
	
	
	virtual void DieProcess() override;
	virtual void GetLifetimeReplicatedProps(TArray<class FLifetimeProperty>& OutLifetimeProps) const override;
	UFUNCTION()
	void OnRep_Weapon();
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
};
