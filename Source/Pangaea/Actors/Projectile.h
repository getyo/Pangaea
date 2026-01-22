// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "Pangaea/Interface/DamageableInterface.h"
#include "Pangaea/Interface/RecycleProjectileInterface.h"
#include "Projectile.generated.h"

UCLASS()
class PANGAEA_API AProjectile : public AActor 
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AProjectile();

protected:
	UPROPERTY(EditAnywhere, Category = "Projectile")
	float Damage = 10.0f;
	UPROPERTY(EditAnywhere, BlueprintReadWrite,Category = "Projectile")
	float Speed = 500.0f;
	UPROPERTY(EditAnywhere, BlueprintReadWrite,Category = "Projectile")
	float LifeSpan = 3.f;
	UPROPERTY(EditAnywhere, BlueprintReadWrite,Category = "Projectile")
	UStaticMeshComponent* MeshComp = nullptr;
	UPROPERTY(EditAnywhere, BlueprintReadWrite,Category = "Projectile")
	UProjectileMovementComponent* ProjectileMovementComponent = nullptr;
	float _LifeCountingDown;
	
	UFUNCTION()
	void OnOverlapBegin(AActor* OverlappedActor,AActor* OtherActor);
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	// Called every frame
	virtual void Tick(float DeltaTime) override;
public:	
	E_Camp Camp;
	IRecycleProjectileInterface *_Holder = nullptr;
	void StartProjectile();
	void ResetProjectile();
	inline UProjectileMovementComponent* GetProjectileMovementComponent() const { return ProjectileMovementComponent; }
};
