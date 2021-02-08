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
	//TODO: 아이템 빈자리 찾아서 추가 
	if (HasEmptySpace(pItemInfo))
	{
		itemContainers.Add(pItemInfo);
	}
}



