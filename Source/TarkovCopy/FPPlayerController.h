// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "FPPlayerController.generated.h"

/**
 * 
 */
UCLASS()
class TARKOVCOPY_API AFPPlayerController : public APlayerController
{
	GENERATED_BODY()
protected: 
	virtual void SetupInputComponent();
	virtual void BeginPlay() override;
private:

public:
	virtual void PlayerTick(float DeltaTime);
	UPROPERTY(EditAnywhere)
	TSubclassOf<UUserWidget> crosshairWidget;
	UPROPERTY(EditAnywhere)
	UUserWidget* crosshair;


};
