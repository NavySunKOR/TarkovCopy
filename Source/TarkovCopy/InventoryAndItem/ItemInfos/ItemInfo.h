// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "ItemInfo.generated.h"

/**
 * 
 */
UCLASS()
class TARKOVCOPY_API UItemInfo : public UObject
{
	GENERATED_BODY()
public:
	//UItemInfo();
	//UItemInfo(float leftPos, float topPos, float width, float height);
	//virtual ~UItemInfo();

	FSlateRect rect;
	UPROPERTY(EditAnywhere)
		int maxCapacity;
	UPROPERTY(EditAnywhere)
		int currentCapacity;
	UPROPERTY(EditAnywhere)
		UTexture* spriteToUse;
	UPROPERTY(EditAnywhere)
		USkeletalMesh* meshToDrop;

	virtual void Use();


};
