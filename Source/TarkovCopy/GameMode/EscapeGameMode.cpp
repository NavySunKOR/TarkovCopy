// Fill out your copyright notice in the Description page of Project Settings.


#include <Kismet/GameplayStatics.h>
#include <Runtime/Engine/Public/EngineUtils.h>
#include <TarkovCopy/Player/Controller/FPPlayerController.h>
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


	UE_LOG(LogTemp, Warning, TEXT("Quest pos"));
	playerCon = Cast<AFPPlayerController>(UGameplayStatics::GetPlayerController(GetWorld(), 0));
	if (playerCon != nullptr)
	{
		UE_LOG(LogTemp, Warning, TEXT("Quest"));
		playerCon->ShowQuestInfo(activeQuestItem->GetName(), (activeQuestItem->GetActorLocation() - playerCon->GetPawn()->GetActorLocation()).Size());
	}

}
void AEscapeGameMode::SelectExfilPoint()
{
	TActorRange<AActor> actorsInWorld = TActorRange<AActor>(GetWorld());
	for (AActor* exfil : actorsInWorld)
	{
		if (exfil->ActorHasTag(FName(TEXT("ExfilPoint"))))
		{
			exfil->SetActorHiddenInGame(true);
			allExfilPoints.Add(exfil);
			UE_LOG(LogTemp, Warning, TEXT("Exfil point name : %s"), exfil);
		}
	}

	int num = FMath::RandRange(0, allExfilPoints.Num() - 1);

	activeExfilPoint = allExfilPoints[num];
	activeExfilPoint->SetActorHiddenInGame(false);

	UE_LOG(LogTemp, Warning, TEXT("Exfil pos"));
	if (playerCon != nullptr)
	{
		UE_LOG(LogTemp, Warning, TEXT("Exfil"));
		playerCon->ShowExfilPoints(activeExfilPoint->GetName(), (activeExfilPoint->GetActorLocation() - playerCon->GetPawn()->GetActorLocation()).Size());
	}
}
void AEscapeGameMode::StartPlay()
{
	Super::StartPlay();
	//SelectQuestItems();
}
void AEscapeGameMode::QuestCompleted(AInteractableObject* questItem)
{
	if (activeQuestItem == questItem)
	{
		isQuestCompleted = true;
		activeQuestItem->SetActorHiddenInGame(true);
		SelectExfilPoint();
	}
}
void AEscapeGameMode::TryExfil()
{
	if (isQuestCompleted)
	{
		//Exfil
		playerCon->Exfiling();
	}
	else
	{
		playerCon->ShowCannotExfil();
	}
}

void AEscapeGameMode::CancelExfil()
{
	playerCon->CancelExfiling();
}