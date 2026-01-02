// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Components//BoxComponent.h"
#include "Components/StaticMeshComponent.h"
#include "ADefenseTower.generated.h"

UCLASS()
class PANGAEA_API ADefenseTower : public AActor
{
	GENERATED_BODY()
	
public:	
	UPROPERTY(EditAnywhere, Category = "TowerParams")
	int HealthPoints = 100;
	UPROPERTY(EditAnywhere, Category = "TowerParams")
	int ShellDefense = 2;
	UPROPERTY(EditAnywhere, Category = "TowerParams")
	float AttackRange = 15.0f;
	UPROPERTY(EditAnywhere, Category = "TowerParams")
	float ReloadInterval = 1.0f;

	// Sets default values for this actor's properties
	ADefenseTower();
	UFUNCTION(BlueprintPure, Category = "Pangaea|DefenseTower")
	int GetHealthPoints();
	UFUNCTION(BlueprintPure, Category = "Pangaea|DefenseTower")
	bool IsDestoryed();
	UFUNCTION(BlueprintPure, Category = "Pangaea|DefenseTower")
	bool CanFire();
	void Fire();
	void Hit(int damage);
	FORCEINLINE UBoxComponent* GetBoxComponent()const {
		return _BoxComponent;
	}
	FORCEINLINE UStaticMeshComponent* GetStaticMeshComponent() const {
		return _StaticMeshComponent;
	}

protected:
	int _HealthPoints;
	float _ReloadCountingDown;
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	void DestoryProcess();
private:
	UPROPERTY(VisibleAnywhere, Category = "Tower Components")
	UBoxComponent* _BoxComponent;
	UPROPERTY(VisibleAnywhere, Category = "Tower Components")
	UStaticMeshComponent* _StaticMeshComponent;
public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
