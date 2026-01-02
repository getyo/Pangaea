// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "AProjectile.generated.h"

UCLASS()
class PANGAEA_API AAProjectile : public AActor
{
	GENERATED_BODY()
	
public:	
	UPROPERTY(EditAnywhere, Category = "ProjectileParams")
	float Damage = 10.0f;
	UPROPERTY(EditAnywhere, Category = "ProjectileParams")
	float Speed = 100.0f;
	UPROPERTY(EditAnywhere, Category = "ProjectileParams")
	int LifeSpan = 5.0f;
	// Sets default values for this actor's properties
	AAProjectile();

protected:
	float _LifeCountingDown;
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
