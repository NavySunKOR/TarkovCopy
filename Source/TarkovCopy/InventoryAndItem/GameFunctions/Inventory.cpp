// Fill out your copyright notice in the Description page of Project Settings.


#include "Inventory.h"

//Inventory::Inventory()
//{
//	backpack.Init(10, 20);
//}

Inventory::Inventory()
{
	//���� �ʱ�ȭ TODO: �Ⱦ��� �ٲ�� �����Ұ�
	backpack.Init(5, 5);
}

Inventory::~Inventory()
{
}

bool Inventory::AddItemToInventory(UItemInfo* item)
{
	return backpack.AddItem(item);
}
