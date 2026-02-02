// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "GeneralCharacterAnimInstance.h"
#include "Pangaea/Interface/DamageableInterface.h"
#include "GeneralCharacter.generated.h"
class AWeapon;

UCLASS()
class PANGAEA_API AGeneralCharacter : public ACharacter,public IDamageableInterface
{
	GENERATED_BODY()

public:
	AGeneralCharacter();
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Character")
	float MaxHealthPoints = 30;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Character")
	float Strength = 10;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Character")
	float AttackInterval = 2;
	float _HitInterval = 0.8;
	UPROPERTY(EditAnywhere, BlueprintReadWrite,Category = "Character")
	E_Camp Camp;
	
	
	UFUNCTION(BlueprintPure, Category = "Character")
	inline float GetHealthPoints() const
	{
		return _CurHealthPoints;
	}
	UFUNCTION(BlueprintPure, Category = "Character")
	inline bool IsKilled() const
	{
		return _CurHealthPoints <= 0;
	}
	inline void SetWeapon(AWeapon * Weapon)
	{
		_Weapon = Weapon;
	}
	UFUNCTION(BlueprintCallable, Category = "Character")
	virtual bool CanAttack();
	UFUNCTION(BlueprintCallable, Category = "Character")
	virtual bool CanHit();
	UFUNCTION(Server, Reliable, BlueprintCallable)
	void AttackC_RPC();
	UFUNCTION(NetMulticast, Reliable, BlueprintCallable)
	void AttackS_BroadCast_RPC();
	UFUNCTION(BlueprintCallable, Category = "Character")
	void Attack();
	virtual void Hurt(float Damage,E_Camp SourceCamp) override;
	UFUNCTION(BlueprintCallable,BlueprintNativeEvent, Category = "Character")
	void DieProcess();
	virtual void DieProcess_Implementation();
	UFUNCTION(Server, Reliable, Category = "Character")
	void RequestDamageToServer(float Damage, E_Camp SourceCamp, AActor* Target);
	
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	UPROPERTY(Replicated,ReplicatedUsing=OnRepCurHealthPoints)
	float _CurHealthPoints;
	UPROPERTY(ReplicatedUsing=OnRep_Weapon)
	AWeapon * _Weapon = nullptr;
	float _AttackCountingDown;
	float _HitCountingDown;
	UGeneralCharacterAnimInstance* _AnimInstance;
	virtual void GetLifetimeReplicatedProps(TArray<class FLifetimeProperty>& OutLifetimeProps) const override;
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
	UFUNCTION(BlueprintCallable,BlueprintNativeEvent, Category = "Character")
	void OnRepCurHealthPoints();
	virtual void OnRepCurHealthPoints_Implementation();
	UFUNCTION()
	void OnRep_Weapon();

};
