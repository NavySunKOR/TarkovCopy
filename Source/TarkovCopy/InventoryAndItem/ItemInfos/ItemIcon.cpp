// Fill out your copyright notice in the Description page of Project Settings.



#include <Components/CanvasPanelSlot.h>
#include "ItemInfo.h"
#include "TarkovCopy/PublicProperty/UMGPublicProperites.h"
#include "ItemIcon.h"

void UItemIcon::Init(UItemInfo* pItemInfo, UInventory* pInven, AFPPlayerController* pController)
{
	itemInfo = pItemInfo;
	invenRef = pInven;
	controllerRef = pController;
	WidgetStyle.Normal.SetResourceObject(pItemInfo->spriteToUse);
	WidgetStyle.Hovered.SetResourceObject(pItemInfo->spriteToUse);
	WidgetStyle.Pressed.SetResourceObject(pItemInfo->spriteToUse);
	UE_LOG(LogTemp, Warning, TEXT("WTF is this? : %d"),Slot);
	UCanvasPanelSlot* canvas = Cast<UCanvasPanelSlot>(Slot);
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
	OnClicked.AddDynamic(this, &UItemIcon::ActionItem);
}

void UItemIcon::ActionItem()
{
	UE_LOG(LogTemp, Warning, TEXT("ActionItems"));
}

void UItemIcon::UseItem()
{

}

void UItemIcon::DropItem()
{

}
