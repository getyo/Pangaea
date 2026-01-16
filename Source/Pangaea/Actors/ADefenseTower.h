// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "../Player/PlayerCharacter.h"
#include "Components/SphereComponent.h"
#include "Components/StaticMeshComponent.h"
#include "ADefenseTower.generated.h"

UCLASS()
class PANGAEA_API ADefenseTower : public AActor
{
	GENERATED_BODY()
	
public:	
	UPROPERTY(EditAnywhere, Category = "DefenseTower")
	int HealthPoints = 100;
	UPROPERTY(EditAnywhere, Category = "DefenseTower")
	int ShellDefense = 2;
	UPROPERTY(EditAnywhere, Category = "DefenseTower")
	float AttackRange = 15.0f;
	UPROPERTY(EditAnywhere, Category = "DefenseTower")
	float ReloadInterval = 1.0f;

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
	int _HealthPoints;
	float _ReloadCountingDown = 0;
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	void DestoryProcess();
	UPROPERTY(EditAnywhere,BlueprintReadWrite, Category = "DefenseTower")
	USphereComponent* SphereComponent;
	UPROPERTY(EditAnywhere,BlueprintReadWrite, Category = "DefenseTower")
	UStaticMeshComponent* StaticMeshComponent;
	UClass* _FireBallClass = nullptr;
	APlayerCharacter* _TargetPlayer;
public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
