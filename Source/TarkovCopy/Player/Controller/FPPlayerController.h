// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include <Components/TextBlock.h>
#include "GameFramework/PlayerController.h"
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
	UPROPERTY(EditAnywhere)
	UUserWidget* crosshair;

	UPROPERTY(EditAnywhere)
	TSubclassOf<UUserWidget> alertHudWidget;
	UPROPERTY(EditAnywhere)
	UUserWidget* alertHud;

	UPROPERTY(EditAnywhere)
	TSubclassOf<UUserWidget> exfilAlertWidget;
	UPROPERTY(EditAnywhere)
	UUserWidget* exfilAlert;

	UTextBlock* alertType;
	UTextBlock* missionObject;
	UTextBlock* range;



	//Exfil°ü·Ã
	bool isExfiling = false;
	UTextBlock* exfilTimer;
	float timeToExfil = 5.f;
	float exfilCounter = 0.f;


	void CloseAlert();
	
public:
	void ShowQuestInfo(FString itemName, float distance);
	void ShowExfilPoints(FString exfilPointsName, float distance);

	void ShowCannotExfil();
	void Exfiling();
	void ExfilingComplete();
	void CancelExfiling();



};
