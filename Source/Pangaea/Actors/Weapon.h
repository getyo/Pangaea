// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Weapon.generated.h"

UCLASS(Blueprintable,BlueprintType)
class PANGAEA_API AWeapon : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AWeapon();
	UFUNCTION()
	void OnWeaponOverlapBegin(AActor* OverlappedActor,AActor* OtherActor);
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	
	UPROPERTY(EditAnywhere,BlueprintReadWrite,Category= "Weapon")
	float Strength;
	UPROPERTY(EditAnywhere,BlueprintReadWrite,Category= "Weapon")
	UStaticMeshComponent * StaticMesh = nullptr;
	ACharacter * _Holder = nullptr;
public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	inline void SetHolder(ACharacter * Holder) { this->_Holder = Holder; }
};
