// Fill out your copyright notice in the Description page of Project Settings.


#include "PickableItem.h"

APickableItem::APickableItem()
{
	root = CreateDefaultSubobject<USceneComponent>(TEXT("createdRoot"));	
	SetRootComponent(root);
	mesh = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("Mesh"));
	mesh->SetupAttachment(root);
}

void APickableItem::BeginPlay()
{
	Super::BeginPlay();
	if (initItem != nullptr)
		Initalize(initItem);
}

void APickableItem::Initalize(TSubclassOf<UItemInfo> pItemInfo)
{
	itemInfo = pItemInfo.GetDefaultObject();
	mesh->SetSkeletalMesh(itemInfo->meshToDrop);
	mesh->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
	mesh->SetSimulatePhysics(true);
}

void APickableItem::Interact()
{
	Super::Interact();
	if (playerCharacter->PickupItem(itemInfo))
		Destroy();
	else
		UE_LOG(LogTemp, Warning, TEXT("Failed to pickup"));
}