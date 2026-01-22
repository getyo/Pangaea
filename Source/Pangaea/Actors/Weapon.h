// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Pangaea/Character/GeneralCharacter.h"
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
	float HitSpan = 1.5;
	UPROPERTY(EditAnywhere,BlueprintReadWrite,Category= "Weapon")
	UStaticMeshComponent * StaticMesh = nullptr;
	UPROPERTY(Replicated)
	AGeneralCharacter * _Holder = nullptr;
	AGeneralCharacter * RPCSender = nullptr;
	float _HitCountDown;
	
	virtual void GetLifetimeReplicatedProps(TArray<class FLifetimeProperty>& OutLifetimeProps) const override;
public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	inline void SetHolder(AGeneralCharacter* Holder) { this->_Holder = Holder; }
};
