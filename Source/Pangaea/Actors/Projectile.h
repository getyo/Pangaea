// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "GameFramework/ProjectileMovementComponent.h"
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
	float LifeSpan = 3.0f;
	UPROPERTY(EditAnywhere, BlueprintReadWrite,Category = "Projectile")
	UStaticMeshComponent* MeshComp = nullptr;
	UPROPERTY(EditAnywhere, BlueprintReadWrite,Category = "Projectile")
	UProjectileMovementComponent* ProjectileMovementComponent = nullptr;
	float _LifeCountingDown;
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	inline UProjectileMovementComponent* GetProjectileMovementComponent() const { return ProjectileMovementComponent; }
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
