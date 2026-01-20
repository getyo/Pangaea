// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "RecycleProjectileInterface.generated.h"
class AProjectile;

UINTERFACE(MinimalAPI, Blueprintable)
class URecycleProjectileInterface : public UInterface
{
	GENERATED_BODY()
};


class PANGAEA_API IRecycleProjectileInterface
{
	GENERATED_BODY()

public:
	virtual void RecycleProjectile(AProjectile * Projectile) = 0;
};
