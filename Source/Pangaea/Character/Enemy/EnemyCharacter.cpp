// Fill out your copyright notice in the Description page of Project Settings.


#include "EnemyCharacter.h"

#include "EnemyAIController.h"
#include "Components/CapsuleComponent.h"
#include "Kismet/KismetMathLibrary.h"
#include "Navigation/PathFollowingComponent.h"
#include "Net/UnrealNetwork.h"
#include "Pangaea/Character/Player/PlayerCharacter.h"

// Sets default values
AEnemyCharacter::AEnemyCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	// Set size for player capsule
	GetCapsuleComponent()->InitCapsuleSize(42.f, 96.0f);

	
	// Don't rotate character to camera direction
	bUseControllerRotationPitch = false;
	bUseControllerRotationYaw = false;
	bUseControllerRotationRoll = false;

	
	PrimaryActorTick.bStartWithTickEnabled = true;
	
	Camp = E_Camp::Enemy;
	PawnSensingComponent = CreateDefaultSubobject<UPawnSensingComponent>("PawnSensingComponent");
	
	static  ConstructorHelpers::FClassFinder<AActor> ClassFinder(TEXT("/Game/TopDown/Blueprints/Actor/BP_WeaponHammer.BP_WeaponHammer_C"));
	if (ClassFinder.Succeeded())
	{
		_WeaponClass = ClassFinder.Class;
	}
	else
	{
		GEngine->AddOnScreenDebugMessage(-1,20.f,FColor::Red,
			FString::Printf(TEXT("Class: %s, Cannot find /Game/TopDown/Blueprints/Actor/BP_WeaponHammer.BP_WeaponHammer_C"),
			*GetClass()->GetName()));
	}
}

// Called when the game starts or when spawned
void AEnemyCharacter::BeginPlay()
{
	Super::BeginPlay();
	if (PawnSensingComponent != nullptr)
	{
		PawnSensingComponent->OnSeePawn.AddDynamic(this,&AEnemyCharacter::ChaseTarget);
	}
	if (HasAuthority())
	{
		_Weapon = Cast<AWeapon>(GetWorld()->SpawnActor(_WeaponClass));
		if (!_Weapon)
		{
			GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Yellow,
				FString::Printf(TEXT("Class %s, Cannot Spawn %s's Actor"),
				*GetName(), *_WeaponClass->GetName()));
		}
		_Weapon->SetOwner(this);
		_Weapon->AttachToComponent(GetMesh(),FAttachmentTransformRules::SnapToTargetIncludingScale,FName("rhand_weapon"));
		_Weapon->SetHolder(this);
	}

}


// Called every frame
void AEnemyCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	
	if (_ChasedTarget != nullptr && _AnimInstance != nullptr && _AnimInstance->GetCharacterAnimStatus() == CharacterStatus::Locomotion)
	{
		auto EnemyController = Cast<AEnemyAIController>(GetController());
		if (EnemyController)
		{
			EnemyController->MakeAttackDecsion(_ChasedTarget);
		}
	}
}

// Called to bind functionality to input
void AEnemyCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
}

void AEnemyCharacter::OnRep_Weapon()
{
	if (_Weapon)
		_Weapon->SetHolder(this);
}

void AEnemyCharacter::ChaseTarget(APawn* SeenPawn)
{
	auto PlayerCharacter = Cast<APlayerCharacter>(SeenPawn);
	if (!PlayerCharacter) return;

	if (_AnimInstance && _AnimInstance->GetCharacterAnimStatus()== CharacterStatus::Locomotion &&
		GetDistanceTo(PlayerCharacter) < ChaseRange)
	{
		auto EnemyController = Cast<AEnemyAIController>(GetController());
		if (EnemyController)
		{
			auto LookAtLocation = UKismetMathLibrary::FindLookAtRotation(GetActorLocation(), SeenPawn->GetActorLocation());
			SetActorRelativeRotation(LookAtLocation);
			EnemyController->MoveTo(SeenPawn->GetActorLocation());
			_ChasedTarget = PlayerCharacter;
		}
	}
	else
	{
		/*GEngine->AddOnScreenDebugMessage(-1,0.5f,FColor::Green,
			FString::Printf(TEXT("AI Status %d"),EnemyAnimInst->GetCharacterAnimStatus()));*/
		/*GEngine->AddOnScreenDebugMessage(-1, 2.f, FColor::Green, 
	FString::Printf(TEXT("ChaseTarget 读取状态为: %d, 时间: %f"), (int)EnemyAnimInst->GetCharacterAnimStatus(), GetWorld()->GetTimeSeconds()));*/
		return;
	}
	
	//设置清理追逐目标的计时器
	GetWorldTimerManager().SetTimer(TargetLostTimerHandle, this, &AEnemyCharacter::ClearTarget, 0.5f, false);
}

bool AEnemyCharacter::CanAttack()
{
	return Super::CanAttack() && _Weapon != nullptr;
}

void AEnemyCharacter::DieProcess()
{
	if (_Weapon)
	{
		_Weapon->SetHolder(nullptr);
		_Weapon->Destroy();
	}
	Super::Destroy();
}

void AEnemyCharacter::GetLifetimeReplicatedProps(TArray<class FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);
	DOREPLIFETIME(AEnemyCharacter,_Weapon);
}


















