#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "DamagableInterface.generated.h"

UENUM(BlueprintType)
enum class E_Camp : uint8
{
	None,
	Enemy,
	Player,
};

UINTERFACE(MinimalAPI, Blueprintable)
class UDamagableInterface: public UInterface
{
	GENERATED_BODY()
};


class PANGAEA_API IDamagableInterface
{
	GENERATED_BODY()

public:
	virtual void Hurt(float Damage,E_Camp SourceCamp) = 0;
};
