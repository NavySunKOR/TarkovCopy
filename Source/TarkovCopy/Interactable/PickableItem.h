// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "InteractableObject.h"
#include "PickableItem.generated.h"

/**
 * 
 */
UCLASS()
class TARKOVCOPY_API APickableItem : public AInteractableObject
{
	GENERATED_BODY()
protected:
	// Called when the game starts
	virtual void BeginPlay() override;
public:
	UPROPERTY(EditAnywhere)
	UItemInfo* itemInfo;

	USceneComponent* root;
	USkeletalMeshComponent* mesh;

	void Initalize(UItemInfo* pItemInfo);

	virtual void Interact() override;
};
