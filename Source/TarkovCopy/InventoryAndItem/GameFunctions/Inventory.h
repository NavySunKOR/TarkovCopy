// Fill out your copyright notice in the Description page of Project Settings.

#pragma once
#include "TarkovCopy/Weapons/BaseGun.h"
#include "TarkovCopy/InventoryAndItem/GameFunctions/Backpack.h"
#include "CoreMinimal.h"

/**
 * 
 */
class TARKOVCOPY_API Inventory
{
public:
	Inventory();
	~Inventory();

	ABaseGun* primaryWeapon;
	ABaseGun* secondaryWeapon;
	
	Backpack backpack;

	bool AddItemToInventory(UItemInfo* item);
};
