// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

/**
 * 
 */
class TARKOVCOPY_API ItemInfo
{
public:
	ItemInfo();
	virtual ~ItemInfo();

	int leftPos;
	int topPos;
	int widthX;
	int widthY;

	int maxCapacity;
	int currentCapacity;
	UTexture* spriteToUse;
	USkeletalMesh* meshToDrop;

	virtual void Use();
};
