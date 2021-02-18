// Fill out your copyright notice in the Description page of Project Settings.



#include <Runtime/UMG/Public/Components/CanvasPanelSlot.h>
#include "TarkovCopy/InventoryAndItem/ItemInfos/ItemInfo.h"
#include "TarkovCopy/PublicProperty/UMGPublicProperites.h"
#include "ItemIcon.h"

void UItemIcon::Init(UItemInfo* pItemInfo)
{
	itemInfo = pItemInfo;
	WidgetStyle.Normal.SetResourceObject(pItemInfo->spriteToUse);
	UE_LOG(LogTemp, Warning, TEXT("WTF is this? : %d"),Slot );
	UCanvasPanelSlot* canvas = Cast<UCanvasPanelSlot>(this->Slot);
	if(canvas != nullptr)
	{
		UE_LOG(LogTemp, Warning, TEXT("Setting size! pos x : %d , y : %d"), itemInfo->left, itemInfo->top);
		canvas->SetSize(FVector2D(itemInfo->width * UMGPublicProperites::BASIC_INVENTORY_GRID_WIDTH, itemInfo->height * UMGPublicProperites::BASIC_INVENTORY_GRID_HEIGHT));
		canvas->SetPosition(FVector2D(itemInfo->left * UMGPublicProperites::BASIC_INVENTORY_GRID_WIDTH, itemInfo->top * UMGPublicProperites::BASIC_INVENTORY_GRID_HEIGHT));
	}
	else
	{

		UE_LOG(LogTemp, Warning, TEXT("Setting size failllllled!"));
	}
}
