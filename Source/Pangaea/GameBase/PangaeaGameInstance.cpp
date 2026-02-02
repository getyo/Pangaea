// Fill out your copyright notice in the Description page of Project Settings.


#include "PangaeaGameInstance.h"
#include "Kismet/GameplayStatics.h"

void UPangaeaGameInstance::StartBasicGame()
{
	auto world = GetWorld();
	if (world)
	{
		UGameplayStatics::OpenLevel(world, "TopDownMap",true,"?listen");
	}
}

void UPangaeaGameInstance::ReturnToPangaeaMainMenu()
{
	auto world = GetWorld();
	if (world)
	{
		UGameplayStatics::OpenLevel(world, "MainMenu",true,"?listen");
	}
}
