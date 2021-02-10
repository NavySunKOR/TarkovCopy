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
	APickableItem();
	virtual void BeginPlay() override;
private:
	UPROPERTY(EditAnywhere)
	TSubclassOf<UItemInfo> initItem;

public:
	UPROPERTY(EditAnywhere)
	UItemInfo* itemInfo;

	USceneComponent* root;
	USkeletalMeshComponent* mesh;

	void Initalize(TSubclassOf<UItemInfo> pItemInfo);

	virtual void Interact() override;
};
