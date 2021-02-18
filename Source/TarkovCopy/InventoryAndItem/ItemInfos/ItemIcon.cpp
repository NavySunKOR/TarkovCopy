// Fill out your copyright notice in the Description page of Project Settings.



#include <Components/CanvasPanelSlot.h>
#include <Blueprint/WidgetTree.h>
#include "ItemInfo.h"
#include "TarkovCopy/PublicProperty/UMGPublicProperites.h"
#include "TarkovCopy/Player/Controller/FPPlayerController.h"
#include "ItemIcon.h"

void UItemIcon::Init(UItemInfo* pItemInfo, UInventory* pInven, AFPPlayerController* pController)
{
	itemInfo = pItemInfo;
	invenRef = pInven;
	controllerRef = pController;
	iconImage = WidgetTree->ConstructWidget<UImage>();
	iconImage->SetBrushFromTexture(pItemInfo->spriteToUse);
	WidgetTree->RootWidget = iconImage;

	UE_LOG(LogTemp, Warning, TEXT("WTF is this? : %d"), Slot);
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
}

void UItemIcon::UseItem()
{
	UE_LOG(LogTemp,Warning,TEXT("UsingItem"))
	bool isEmpty = invenRef->UseItem(itemInfo);
	if (isEmpty)
	{
		RemoveFromParent();
	}
}

void UItemIcon::DropItem()
{
	UE_LOG(LogTemp, Warning, TEXT("DropItem"))
	bool isEmpty = invenRef->DropItem(itemInfo);
	if (isEmpty)
	{
		RemoveFromParent();
	}
}

//FEventReply UItemIcon::OnMouseButtonDown(FGeometry MyGeometry, const FPointerEvent& MouseEvent)
//{
//	Super::OnMouseButtonDown(MyGeometry, MouseEvent);
//	UE_LOG(LogTemp, Warning, TEXT("Clicked! !! "));
//	if (MouseEvent.IsMouseButtonDown(EKeys::RightMouseButton))
//	{
//		DropItem();
//	}
//	else if (MouseEvent.IsMouseButtonDown(EKeys::LeftMouseButton))
//	{
//		UseItem();
//	}
//
//	return FEventReply(true);
//}
//
//void UItemIcon::OnMouseEnter(FGeometry MyGeometry, const FPointerEvent& MouseEvent)
//{
//	Super::OnMouseEnter(MyGeometry, MouseEvent);
//	UE_LOG(LogTemp, Warning, TEXT("Backaw34er"));
//}
