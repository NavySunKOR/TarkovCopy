// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "TarkovCopy/Weapons/BaseGun.h"
#include "TarkovCopy/InventoryAndItem/GameFunctions/Backpack.h"
#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "Inventory.generated.h"

/**
 * 
 */
UCLASS(Blueprintable, BlueprintType)
class TARKOVCOPY_API UInventory : public UObject
{
	GENERATED_BODY()
public:
	ABaseGun* primaryWeapon;
	ABaseGun* secondaryWeapon;

	UPROPERTY(EditAnywhere)
	TSubclassOf<UBackpack> backpackType;
	UBackpack* backpack;

	void Init();
	bool AddItemToInventory(UItemInfo* item);

	UFUNCTION(BlueprintPure)
	UBackpack* GetBackpack();

};
