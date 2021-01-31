// Fill out your copyright notice in the Description page of Project Settings.


#include <Kismet/GameplayStatics.h>
#include <Runtime/Engine/Public/EngineUtils.h>
#include "EscapeGameMode.h"

void AEscapeGameMode::SelectQuestItems()
{
	TActorRange<AQuestItem> items = TActorRange<AQuestItem>(GetWorld());
	for (AQuestItem* item : items)
	{
		UE_LOG(LogTemp, Warning, TEXT("Item found : %s"), *item->GetName());
		item->SetActorHiddenInGame(true);
		allQuestItems.Add(item);
	}
	
	int num = FMath::RandRange(0, allQuestItems.Num() - 1);

	activeQuestItem = allQuestItems[num];
	activeQuestItem->SetActorHiddenInGame(false);
}
void AEscapeGameMode::SelectExfilPoint()
{

}
void AEscapeGameMode::InitGame(const FString& MapName, const FString& Options, FString& ErrorMessage)
{
	Super::InitGame(MapName, Options, ErrorMessage);
	SelectQuestItems();
}
void AEscapeGameMode::QuestCompleted(AInteractableObject* questItem)
{
	if (activeQuestItem == questItem)
	{
		isQuestCompleted = true;
		activeQuestItem->SetActorHiddenInGame(true);
	}
}
void AEscapeGameMode::TryExfil()
{
	if (isQuestCompleted)
	{
		//Exfil
	}
}
