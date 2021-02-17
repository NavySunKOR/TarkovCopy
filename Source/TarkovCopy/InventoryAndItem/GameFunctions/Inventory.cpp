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

UBackpack* UInventory::GetBackpack()
{
	return backpack;
}
