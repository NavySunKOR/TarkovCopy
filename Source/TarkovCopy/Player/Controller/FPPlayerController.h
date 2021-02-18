// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include <Components/TextBlock.h>
#include <Components/CanvasPanel.h>
#include "GameFramework/PlayerController.h"
#include "TarkovCopy/InventoryAndItem/ItemInfos/ItemIcon.h"
#include "FPPlayerController.generated.h"

/**
 * 
 */
UCLASS()
class TARKOVCOPY_API AFPPlayerController : public APlayerController
{
	GENERATED_BODY()
//Generated
protected: 
	virtual void SetupInputComponent();
	virtual void BeginPlay() override;
public:
	virtual void PlayerTick(float DeltaTime);

//Created
private:
	UPROPERTY(EditAnywhere)
	TSubclassOf<UUserWidget> crosshairWidget;
	UUserWidget* crosshair;

	UPROPERTY(EditAnywhere)
	TSubclassOf<UUserWidget> alertHudWidget;
	UUserWidget* alertHud;

	UPROPERTY(EditAnywhere)
	TSubclassOf<UUserWidget> exfilAlertWidget;
	UUserWidget* exfilAlert;


	//TODO: UI관련, 추 후에 컨트롤러로 옮길것
	UPROPERTY(EditAnywhere)
	TSubclassOf<UUserWidget> inventoryWidget;
	UPROPERTY(EditAnywhere)
	TSubclassOf<UItemIcon> iconWidget;
	UUserWidget* inventory;
	UCanvasPanel* itemContainer;
	TArray<UItemIcon*> items;


	UTextBlock* alertType;
	UTextBlock* missionObject;
	UTextBlock* range;



	//Exfil관련
	bool isExfiling = false;
	UTextBlock* exfilTimer;
	float timeToExfil = 5.f;
	float exfilCounter = 0.f;


	void CloseAlert();
	
public:
	bool isInventoryOpened;
	void InitInvenotry();
	void OpenCloseInventory();
	void AddItem(UItemInfo* itemInfo);

	void ShowQuestInfo(FString itemName, float distance);
	void ShowExfilPoints(FString exfilPointsName, float distance);

	void ShowCannotExfil();
	void Exfiling();
	void ExfilingComplete();
	void CancelExfiling();



};
