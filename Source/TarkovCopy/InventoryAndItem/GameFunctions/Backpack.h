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
	bool** invenVisualize;


	TArray<UItemInfo*> itemContainers;

	void Init();

	bool HasEmptySpace(UItemInfo* pItemInfo);
	bool IsIntersected(UItemInfo* pItemInfo);
	void AddItem(UItemInfo* pItemInfo);
private:
	bool HasEmptySpaceWidthAxis(UItemInfo* pItemInfo);

	bool HasEmptySpaceHeightAxis(UItemInfo* pItemInfo);

};
