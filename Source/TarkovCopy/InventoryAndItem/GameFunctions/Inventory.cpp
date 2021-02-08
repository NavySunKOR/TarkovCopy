// Fill out your copyright notice in the Description page of Project Settings.


#include "Inventory.h"

Inventory::Inventory()
{
}

Inventory::~Inventory()
{
}

void Inventory::AddItemToInventory(ItemInfo item)
{
	backpack.AddItem(item);
}
