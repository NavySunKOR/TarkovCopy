// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "TarkovCopy/InventoryAndItem/ItemInfos/ItemInfo.h"
#include "Components/Image.h"
#include "ItemIcon.generated.h"

/**
 * 
 */
UCLASS()
class TARKOVCOPY_API UItemIcon : public UImage
{
	GENERATED_BODY()
	
public:
	UItemInfo* itemInfo;
	void Init(UItemInfo* pItemInfo);

};
