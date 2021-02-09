// Fill out your copyright notice in the Description page of Project Settings.

#include <Layout/SlateRect.h>
#include "Backpack.h"

Backpack::Backpack()
{
}

Backpack::~Backpack()
{
}

bool Backpack::HasEmptySpace(UItemInfo* pItemInfo)
{
	for (int i = 0; i < itemContainers.Num(); i++)
	{
		if (FSlateRect::DoRectanglesIntersect(itemContainers[i]->rect, pItemInfo->rect))
			return false;
	}

	return true;
}

void Backpack::AddItem(UItemInfo* pItemInfo)
{
	//TODO: 아이템 빈자리 찾아서 추가 
	if (HasEmptySpace(pItemInfo))
	{
		itemContainers.Add(pItemInfo);
	}
}



