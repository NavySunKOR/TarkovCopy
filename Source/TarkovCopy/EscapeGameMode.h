// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "TarkovCopyGameModeBase.h"
#include "TarkovCopy/QuestItem.h"
#include "EscapeGameMode.generated.h"

/**
 * 
 */
UCLASS()
class TARKOVCOPY_API AEscapeGameMode : public ATarkovCopyGameModeBase
{
	GENERATED_BODY()

private:
	TArray<AQuestItem*> allQuestItems;

	UPROPERTY(EditAnywhere)
	AQuestItem* activeQuestItem;

	bool isQuestCompleted = false;


	void SelectQuestItems();
	void SelectExfilPoint();

public:
	virtual void InitGame(const FString& MapName, const FString& Options, FString& ErrorMessage) override;
	virtual void QuestCompleted(AInteractableObject* questItem) override;
	virtual void TryExfil() override;
};
