 // Fill out your copyright notice in the Description page of Project Settings.


#include "Inventory.h"

void UInventory::Init()
{
	backpack = backpackType.GetDefaultObject();
	backpack->Init();
}

bool UInventory::AddItemToInventory(UItemInfo* item)
{
	return backpack->AddItem(item);
}

bool UInventory::UseItem(UItemInfo* pItem)
{
	UItemInfo* foundItem = backpack->GetItemReference(pItem);
	return foundItem->Use();
}

bool UInventory::DropItem(UItemInfo* pItem)
{
	UItemInfo* foundItem = backpack->GetItemReference(pItem);
	return foundItem->DropItem();
}

UBackpack* UInventory::GetBackpack()
{
	return backpack;
}
