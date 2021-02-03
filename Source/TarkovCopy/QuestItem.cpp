// Fill out your copyright notice in the Description page of Project Settings.


#include <TarkovCopy/EscapeGameMode.h>
#include "QuestItem.h"

void AQuestItem::Interact()
{
	Super::Interact();
	GetWorld()->GetAuthGameMode<AEscapeGameMode>()->QuestCompleted(this);
}