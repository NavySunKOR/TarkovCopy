// Fill out your copyright notice in the Description page of Project Settings.


#include "ItemInfo.h"

ItemInfo::ItemInfo()
{
}

ItemInfo::~ItemInfo()
{
	delete spriteToUse;
	delete meshToDrop;
}

void ItemInfo::Use()
{
	--currentCapacity;
}
