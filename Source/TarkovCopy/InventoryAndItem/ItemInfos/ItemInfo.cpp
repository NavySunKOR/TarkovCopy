// Fill out your copyright notice in the Description page of Project Settings.


#include "ItemInfo.h"

//UItemInfo::UItemInfo()
//{
//	rect = FSlateRect();
//	rect.Left = 0;
//	rect.Top = 0;
//	rect.Right = 0;
//	rect.Bottom = 0;
//}
//
//UItemInfo::UItemInfo(float leftPos, float topPos, float width, float height)
//{
//	rect = FSlateRect(leftPos, topPos, leftPos + width, topPos - height);
//}
//
//UItemInfo::~UItemInfo()
//{
//	delete spriteToUse;
//	delete meshToDrop;
//}
void UItemInfo::InitRect(float pLeft, float pTop)
{
	rect = FSlateRect();
	left = pLeft;
	top = pTop;
	rect.Left = left;
	rect.Top = top;
	rect.Right = left + width;
	rect.Bottom = top - height;
}
void UItemInfo::Use()
{
	--currentCapacity;
}
