// Fill out your copyright notice in the Description page of Project Settings.


#include "PickableItem.h"

void APickableItem::BeginPlay()
{
	Super::BeginPlay();
}

void APickableItem::Initalize(ItemInfo pItemInfo)
{
	itemInfo = pItemInfo;
	root = CreateDefaultSubobject<USceneComponent>(TEXT("Root"));
	SetRootComponent(root);
	mesh = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("Mesh"));
	mesh->SetupAttachment(root);
	mesh->SetSkeletalMesh(itemInfo.meshToDrop);
}

void APickableItem::Interact()
{
	Super::Interact();
	playerCharacter->PickupItem(itemInfo);
	Destroy();
}