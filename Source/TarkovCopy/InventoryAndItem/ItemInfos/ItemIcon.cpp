// Fill out your copyright notice in the Description page of Project Settings.



#include <Runtime/UMG/Public/Components/CanvasPanelSlot.h>
#include "TarkovCopy/InventoryAndItem/ItemInfos/ItemInfo.h"
#include "TarkovCopy/PublicProperty/UMGPublicProperites.h"
#include "ItemIcon.h"

void UItemIcon::Init(UItemInfo* pItemInfo)
{
	itemInfo = pItemInfo;
	SetBrushFromTexture(pItemInfo->spriteToUse);
	UE_LOG(LogTemp, Warning, TEXT("WTF is this? : %d"),Slot );
	UCanvasPanelSlot* canvas = Cast<UCanvasPanelSlot>(this->Slot);
	if(canvas != nullptr)
	{
		UE_LOG(LogTemp, Warning, TEXT("Setting size!"));
		canvas->SetSize(FVector2D(itemInfo->width * UMGPublicProperites::BASIC_INVENTORY_GRID_WIDTH, itemInfo->height * UMGPublicProperites::BASIC_INVENTORY_GRID_HEIGHT));
		canvas->SetPosition(FVector2D(itemInfo->left, itemInfo->top));
	}
	else
	{

		UE_LOG(LogTemp, Warning, TEXT("Setting size failllllled!"));
	}
}
