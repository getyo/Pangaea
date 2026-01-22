// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "GeneralCharacterAnimInstance.h"
#include "Pangaea/Interface/DamageableInterface.h"
#include "GeneralCharacter.generated.h"

UCLASS()
class PANGAEA_API AGeneralCharacter : public ACharacter,public IDamageableInterface
{
	GENERATED_BODY()

public:
	AGeneralCharacter();
	UPROPERTY(EditAnywhere, Category = "Character")
	int MaxHealthPoints = 30;
	UPROPERTY(EditAnywhere, Category = "Character")
	float Strength = 10;
	UPROPERTY(EditAnywhere, Category = "Character")
	float AttackInterval = 2;
	float _HitInterval = 0.8;
	UPROPERTY(EditAnywhere, BlueprintReadWrite,Category = "Character")
	E_Camp Camp;
	
	
	UFUNCTION(BlueprintPure, Category = "Character")
	inline int GetHealthPoints() const
	{
		return _CurHealthPoints;
	}
	UFUNCTION(BlueprintPure, Category = "Character")
	inline bool IsKilled() const
	{
		return _CurHealthPoints <= 0;
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
	UFUNCTION(BlueprintCallable, Category = "Character")
	virtual void DieProcess()
	{
		Destroy();
	}
	UFUNCTION(Server, Reliable, Category = "Character")
	void RequestDamageToServer(float Damage, E_Camp SourceCamp, AActor* Target);
	
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	UPROPERTY(Replicated,ReplicatedUsing=OnRep_CurHealthPoints)
	int _CurHealthPoints;
	float _AttackCountingDown;
	float _HitCountingDown;
	UGeneralCharacterAnimInstance* _AnimInstance;
	virtual void GetLifetimeReplicatedProps(TArray<class FLifetimeProperty>& OutLifetimeProps) const override;
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
	UFUNCTION(BlueprintCallable, Category = "Character")
	virtual void OnRep_CurHealthPoints();
private:	

};
