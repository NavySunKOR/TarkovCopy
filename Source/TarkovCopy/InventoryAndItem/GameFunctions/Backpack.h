// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "TarkovCopy/InventoryAndItem/ItemInfos/ItemInfo.h"
#include "CoreMinimal.h"

/**
 * 
 */
class TARKOVCOPY_API Backpack
{
public:
	Backpack();
	~Backpack();
	
	int capacityWidth;
	int capacityHeight;

	TArray<ItemInfo> itemContainers;
	bool HasEmptySpace(ItemInfo pItemInfo);
	void AddItem(ItemInfo pItemInfo);


};
