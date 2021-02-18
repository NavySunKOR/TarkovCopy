// Fill out your copyright notice in the Description page of Project Settings.

#include <GameFramework/PlayerInput.h>
#include <GameFramework/Character.h>
#include <Kismet/GameplayStatics.h>
#include <Blueprint/WidgetTree.h>
#include <Blueprint/UserWidget.h>
#include <Components/CanvasPanelSlot.h>
#include <TimerManager.h>
#include "TarkovCopy/GameMode/EscapeGameMode.h"
#include "TarkovCopy/PublicProperty/UMGPublicProperites.h"
#include "FPPlayerController.h"

void AFPPlayerController::BeginPlay()
{
	crosshair = CreateWidget<UUserWidget>(this, crosshairWidget);
	crosshair->AddToViewport();
	
	alertHud = CreateWidget<UUserWidget>(this, alertHudWidget);
	alertHud->AddToViewport();

	exfilAlert = CreateWidget<UUserWidget>(this, exfilAlertWidget);
	exfilAlert->AddToViewport();

	UE_LOG(LogTemp, Warning, TEXT("PlayerUIInit"));

	alertHud->SetVisibility(ESlateVisibility::Hidden);
	exfilAlert->SetVisibility(ESlateVisibility::Hidden);

	alertType = Cast<UTextBlock>(alertHud->GetWidgetFromName(TEXT("AlertType")));
	missionObject = Cast<UTextBlock>(alertHud->GetWidgetFromName(TEXT("Object")));
	range = Cast<UTextBlock>(alertHud->GetWidgetFromName(TEXT("Range")));
	exfilTimer = Cast<UTextBlock>(exfilAlert->GetWidgetFromName(TEXT("ExfilTimer")));

	AEscapeGameMode* gameMode = GetWorld()->GetAuthGameMode<AEscapeGameMode>();
	if(gameMode)
		gameMode->SelectQuestItems();

}

void AFPPlayerController::SetupInputComponent()
{

}




void AFPPlayerController::PlayerTick(float DeltaTime)
{
	Super::PlayerTick(DeltaTime);
	if (isExfiling)
	{
		exfilCounter += DeltaTime;
		exfilTimer->SetText(FText::FromString(FString::FormatAsNumber(timeToExfil - exfilCounter)));
		if ((timeToExfil - exfilCounter) <= 0.f)
		{
			ExfilingComplete();
		}
	}
}

void AFPPlayerController::InitInvenotry()
{
	APlayerCharacter* character = Cast<APlayerCharacter>(GetPawn());
	inventory = CreateWidget<UUserWidget>(this, inventoryWidget);
	UE_LOG(LogTemp, Warning, TEXT("Grande : %s"), *character->inventory->backpack->GetBackpackSize().ToString());

	itemContainer = Cast<UCanvasPanel>(inventory->GetWidgetFromName(TEXT("ItemContainer")));
	if (itemContainer == nullptr)
	{
		UE_LOG(LogTemp, Warning, TEXT("Gone burst!"));
	}
	UCanvasPanelSlot* backgroundImage  = Cast<UCanvasPanelSlot>(inventory->GetWidgetFromName(TEXT("Background"))->Slot);
	if (backgroundImage != nullptr && itemContainer != nullptr)
	{
		backgroundImage->SetSize(FVector2D(UMGPublicProperites::BASIC_INVENTORY_GRID_WIDTH, UMGPublicProperites::BASIC_INVENTORY_GRID_HEIGHT) * character->inventory->backpack->GetBackpackSize());
		UCanvasPanelSlot* canva = Cast<UCanvasPanelSlot>(itemContainer->Slot);
		if (canva != nullptr)
			canva->SetSize(FVector2D(UMGPublicProperites::BASIC_INVENTORY_GRID_WIDTH, UMGPublicProperites::BASIC_INVENTORY_GRID_HEIGHT) * character->inventory->backpack->GetBackpackSize());
	}
	else
		UE_LOG(LogTemp, Warning, TEXT("Canvas is null!"));
}

void AFPPlayerController::OpenCloseInventory()
{
	if (inventory->IsInViewport())
	{
		bShowMouseCursor = false;
		bEnableClickEvents = false;
		bEnableMouseOverEvents = false;
		SetIgnoreLookInput(false);
		SetIgnoreMoveInput(false);
		isInventoryOpened = false;
		inventory->RemoveFromViewport();
	}
	else
	{
		bShowMouseCursor = true;
		bEnableClickEvents = true;
		bEnableMouseOverEvents = true;
		isInventoryOpened = true;
		SetIgnoreLookInput(true);
		SetIgnoreMoveInput(true);
		inventory->AddToViewport();
	}
}

void AFPPlayerController::AddItem(UItemInfo* itemInfo, UInventory* pInvenRef)
{

	UItemIcon* uiItem = inventory->WidgetTree->ConstructWidget<UItemIcon>(iconWidget);

	UCanvasPanelSlot* panelSlotForItem = Cast<UCanvasPanelSlot>(itemContainer->AddChild(uiItem));
	uiItem->Slot = panelSlotForItem;

	uiItem->Init(itemInfo, pInvenRef, this);
	UE_LOG(LogTemp, Warning, TEXT("Successfully added"));
	items.Add(uiItem);
	UE_LOG(LogTemp, Warning, TEXT("Destructable damned"));
}

void AFPPlayerController::ShowQuestInfo(FString itemName, float distance)
{
	alertHud->SetVisibility(ESlateVisibility::Visible);
	alertType->SetText(FText::FromString("Quest"));

	FString objectMessage = "Get the ";
	objectMessage.Append(itemName);
	missionObject->SetText(FText::FromString(objectMessage));

	FString rangeText = FString::FormatAsNumber((int)distance);
	rangeText.Append("m");
	range->SetText(FText::FromString(rangeText));

	FTimerHandle timers;
	GetWorldTimerManager().SetTimer(timers,this,&AFPPlayerController::CloseAlert, 3.f, false);
}

void AFPPlayerController::ShowExfilPoints(FString exfilPointsName, float distance)
{
	alertHud->SetVisibility(ESlateVisibility::Visible);

	alertType->SetText(FText::FromString("Exfil"));

	FString objectMessage = "Get to the ";
	objectMessage.Append(exfilPointsName);
	missionObject->SetText(FText::FromString(objectMessage));

	FString rangeText = FString::FormatAsNumber((int)distance);
	rangeText.Append("m");
	range->SetText(FText::FromString(rangeText));

	FTimerHandle timers;
	GetWorldTimerManager().SetTimer(timers, this, &AFPPlayerController::CloseAlert, 3.f, false);
}


void AFPPlayerController::ShowCannotExfil()
{
	UE_LOG(LogTemp, Warning, TEXT("Can not exfil!"));
}

void AFPPlayerController::Exfiling()
{
	if (!isExfiling)
	{
		isExfiling = true;
		exfilCounter = 0.f;
		exfilAlert->SetVisibility(ESlateVisibility::Visible);
		UE_LOG(LogTemp, Warning, TEXT("Exfiling......"));
	}
}

void AFPPlayerController::ExfilingComplete()
{
	UE_LOG(LogTemp, Warning, TEXT("ExfilingComplete"));
	isExfiling = false;
	exfilAlert->SetVisibility(ESlateVisibility::Hidden);
}

void AFPPlayerController::CancelExfiling()
{
	if (isExfiling)
	{
		isExfiling = false;
		exfilAlert->SetVisibility(ESlateVisibility::Hidden);
		UE_LOG(LogTemp, Warning, TEXT("Cancel exfiling....."));
	}
}

void AFPPlayerController::CloseAlert()
{
	alertHud->SetVisibility(ESlateVisibility::Hidden);
}
