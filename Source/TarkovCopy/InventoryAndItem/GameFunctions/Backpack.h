// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "TarkovCopy/InventoryAndItem/ItemInfos/ItemInfo.h"
#include "Backpack.generated.h"

/**
 * 
 */
UCLASS(Blueprintable, BlueprintType)
class TARKOVCOPY_API UBackpack : public UObject
{
	GENERATED_BODY()
private:
	bool** invenVisualize;
	TArray<UItemInfo*> itemContainers;
	std::tuple<bool, int, int> HasEmptySpaceWidthAxis(UItemInfo* pItemInfo);
	std::tuple<bool, int, int> HasEmptySpaceHeightAxis(UItemInfo* pItemInfo);
	void UpdateInvenVisualize(UItemInfo* pItemInfo);

public:
	UPROPERTY(EditAnywhere)
	int capacityWidth;
	UPROPERTY(EditAnywhere)
	int capacityHeight;

	void Init();
	std::tuple<bool, int, int> HasEmptySpace(UItemInfo* pItemInfo);
	bool IsIntersected(UItemInfo* pItemInfo);
	bool AddItem(UItemInfo* pItemInfo);
	UItemInfo* GetItemReference(UItemInfo* pItemPtr);
	FVector2D GetBackpackSize();
};
