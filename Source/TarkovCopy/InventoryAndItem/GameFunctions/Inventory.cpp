// Fill out your copyright notice in the Description page of Project Settings.


#include "Inventory.h"

//Inventory::Inventory()
//{
//	backpack.Init(10, 20);
//}

Inventory::Inventory()
{
	//가방 초기화 TODO: 픽어블로 바뀌면 제거할것
	backpack.Init(5, 5);
}

Inventory::~Inventory()
{
}

bool Inventory::AddItemToInventory(UItemInfo* item)
{
	return backpack.AddItem(item);
}
