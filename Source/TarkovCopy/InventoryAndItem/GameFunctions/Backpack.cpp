// Fill out your copyright notice in the Description page of Project Settings.


#include "Backpack.h"

Backpack::Backpack()
{
}

Backpack::~Backpack()
{
}

bool Backpack::HasEmptySpace(ItemInfo pItemInfo)
{
	return false;
}

void Backpack::AddItem(ItemInfo pItemInfo)
{
	//TODO: ������ ���ڸ� ã�Ƽ� �߰� 
	if (HasEmptySpace(pItemInfo))
	{
		itemContainers.Add(pItemInfo);
	}
}



