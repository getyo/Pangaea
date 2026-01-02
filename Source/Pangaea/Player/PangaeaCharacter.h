// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "PangaeaCharacter.generated.h"

UCLASS(Blueprintable)
class APangaeaCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	APangaeaCharacter();

	// Called every frame.
	virtual void Tick(float DeltaSeconds) override;
	UPROPERTY(EditAnywhere, Category = "PlayerAvatar Params")
	int HealthPoints = 500;
	UPROPERTY(EditAnywhere, Category = "PlayerAvatar Params")
	float Strength = 10;
	UPROPERTY(EditAnywhere, Category = "PlayerAvatar Params")
	float Armer = 3;
	UPROPERTY(EditAnywhere, Category = "PlayerAvatar Params")
	float AttackRange = 6;
	UPROPERTY(EditAnywhere, Category = "PlayerAvatar Params")
	float AttackInterval = 2;

	UFUNCTION(BlueprintPure, Category = "Pangaea|PlayerAvatar")
	inline int GetHealthPoints() const { return _HealthPoints; }
	UFUNCTION(BlueprintPure, Category = "Pangaea|PlayerAvatar")
	inline bool IsKilled() const
	{
		return HealthPoints <= 0;
	}
	UFUNCTION(BlueprintCallable, Category = "Pangaea|PlayerAvatar")
	bool CanAttack();
	void Attack();
	void Hit(int damage);
	
	/** Returns TopDownCameraComponent subobject **/
	FORCEINLINE class UCameraComponent* GetTopDownCameraComponent() const { return TopDownCameraComponent; }
	/** Returns CameraBoom subobject **/
	FORCEINLINE class USpringArmComponent* GetCameraBoom() const { return CameraBoom; }

private:
	/** Top down camera */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	class UCameraComponent* TopDownCameraComponent;

	/** Camera boom positioning the camera above the character */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	class USpringArmComponent* CameraBoom;
	UFUNCTION(BlueprintCallable, Category = "Pangaea|PlayerAvatar" ,meta = (AllowPrivateAccess = "true"))
	void DieProcess();
protected:
	int _HealthPoints;
	float _AttackCountingDown;
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
};

