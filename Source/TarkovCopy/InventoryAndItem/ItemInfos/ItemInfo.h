// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "ItemInfo.generated.h"

/**
 * 
 */
UCLASS(Blueprintable, BlueprintType)
class TARKOVCOPY_API UItemInfo : public UObject
{
	GENERATED_BODY()
public:
	//UItemInfo();
	//UItemInfo(float leftPos, float topPos, float width, float height);
	//virtual ~UItemInfo();

	UPROPERTY(EditAnywhere)
	float width;
	UPROPERTY(EditAnywhere)
	float height;

	float left;
	float top;

	UPROPERTY(EditAnywhere)
	int maxCapacity;
	UPROPERTY(EditAnywhere)
	int currentCapacity;
	UPROPERTY(EditAnywhere)
	UTexture* spriteToUse;
	UPROPERTY(EditAnywhere)
	USkeletalMesh* meshToDrop;


	FSlateRect rect;

	virtual void Use();
	virtual void InitRect(float pCenterX, float pCenterY);


};
