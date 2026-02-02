// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Projectile.h"
#include "GameFramework/Actor.h"
#include "Pangaea/Character//Player/PlayerCharacter.h"
#include "Components/SphereComponent.h"
#include "Components/StaticMeshComponent.h"
#include "Pangaea/Interface/RecycleProjectileInterface.h"
#include "Pangaea/Interface/DamageableInterface.h"
#include "ADefenseTower.generated.h"

UCLASS()
class PANGAEA_API ADefenseTower : public AActor,public IRecycleProjectileInterface,public IDamageableInterface
{
	GENERATED_BODY()
	
public:	
	UPROPERTY(EditAnywhere, Category = "DefenseTower")
	int MaxHealthPoints = 100;
	UPROPERTY(EditAnywhere, Category = "DefenseTower")
	int ShellDefense = 2;
	UPROPERTY(EditAnywhere, Category = "DefenseTower")
	float AttackRange = 15.0f;
	UPROPERTY(EditAnywhere, Category = "DefenseTower")
	float ReloadInterval = 2.0f;
	UPROPERTY(EditAnywhere,BlueprintReadWrite, Category = "DefenseTower")
	E_Camp Camp = E_Camp::Enemy;
	
	// Sets default values for this actor's properties
	ADefenseTower();
	UFUNCTION(BlueprintPure, Category = "DefenseTower")
	int GetHealthPoints();
	UFUNCTION(BlueprintPure, Category = "DefenseTower")
	bool IsDestoryed();
	UFUNCTION(BlueprintPure, Category = "DefenseTower")
	bool CanFire();
	void Fire();
	void Hit(int damage);
	UFUNCTION()
	void OnSphereOverlapBegin(UPrimitiveComponent * OverlappedComponent,
		AActor * OtherActor,
		UPrimitiveComponent * OtherComp,
		int OtherBodyIndex,
		bool bFromSweep,
		const FHitResult & SweepResult);
	UFUNCTION()
	void OnSphereOverlapEnd(UPrimitiveComponent * OverlappedComponent,
		AActor * OtherActor,
		UPrimitiveComponent * OtherComp,
		int OtherBodyIndex);


protected:
	UPROPERTY(EditAnywhere,BlueprintReadWrite, Category = "DefenseTower")
	USphereComponent* SphereComponent;
	UPROPERTY(EditAnywhere,BlueprintReadWrite, Category = "DefenseTower")
	UStaticMeshComponent* StaticMeshComponent;
	UPROPERTY(ReplicatedUsing=OnRep_HealthPoints)
	int _HealthPoints;
	float _ReloadCountingDown = 0;
	UClass* _FireBallClass = nullptr;
	APlayerCharacter* _TargetPlayer;
	TQueue<AProjectile *> _ProjectPool;
	
	AProjectile* GetProjectile(UClass * ProjectClass,const UObject * Context);
	virtual void BeginPlay() override;
	virtual void RecycleProjectile(AProjectile * Projectile) override;
	virtual void Hurt(float Damage, E_Camp SourceCamp) override;
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent,Category = "DefenseTower")
	void DestroyProcess();
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	virtual void GetLifetimeReplicatedProps(TArray<class FLifetimeProperty>& OutLifetimeProps) const override;
	UFUNCTION()
	void OnRep_HealthPoints();
	UFUNCTION(Client,Reliable,NetMulticast)
	void FireBallSpawn_BroadCast_RPC();
public:	

};
