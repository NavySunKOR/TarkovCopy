// Fill out your copyright notice in the Description page of Project Settings.

#include <GameFramework/PlayerInput.h>
#include <GameFramework/Character.h>
#include <Kismet/GameplayStatics.h>
#include <Blueprint/UserWidget.h>
#include <Components/CanvasPanelSlot.h>
#include <TarkovCopy/GameMode/EscapeGameMode.h>
#include <TimerManager.h>
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
	inventory->AddToViewport();
	UE_LOG(LogTemp, Warning, TEXT("sizeOfGrid : %s"), *sizeOfGrid.ToString());
	UE_LOG(LogTemp, Warning, TEXT("Grande : %s"), *character->inventory->backpack->GetBackpackSize().ToString());

	UCanvasPanelSlot* canvasPanel = Cast<UCanvasPanelSlot>(inventory->GetWidgetFromName(TEXT("Background"))->Slot);
	if (canvasPanel != nullptr)
		canvasPanel->SetSize(sizeOfGrid * character->inventory->backpack->GetBackpackSize());
	else
		UE_LOG(LogTemp, Warning, TEXT("Canvas is null! "));
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
