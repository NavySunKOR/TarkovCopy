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

	std::tuple<bool,int,int> HasEmptySpace(UItemInfo* pItemInfo);
	bool IsIntersected(UItemInfo* pItemInfo);
	void AddItem(UItemInfo* pItemInfo);
private:
	std::tuple<bool, int, int> HasEmptySpaceWidthAxis(UItemInfo* pItemInfo);
	std::tuple<bool, int, int> HasEmptySpaceHeightAxis(UItemInfo* pItemInfo);

	void UpdateInvenVisualize(UItemInfo* pItemInfo);


};
