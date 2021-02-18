// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include <Components/Button.h>
#include <Components/Image.h>
#include "ItemIcon.generated.h"

class UItemInfo;
class UInventory;
class AFPPlayerController;

/**
 * 
 */
UCLASS()
class TARKOVCOPY_API UItemIcon : public UButton
{
	GENERATED_BODY()
	
public:
	UItemInfo* itemInfo;
	UImage* iconImage;
	UInventory* invenRef;
	AFPPlayerController* controllerRef;

	UFUNCTION()
	void ActionItem();
	void UseItem();
	void DropItem();
	void Init(UItemInfo* pItemInfo, UInventory* pInven, AFPPlayerController* pController);
	
};
