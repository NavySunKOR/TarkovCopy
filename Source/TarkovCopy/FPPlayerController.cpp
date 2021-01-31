// Fill out your copyright notice in the Description page of Project Settings.

#include <GameFramework/PlayerInput.h>
#include <GameFramework/Character.h>
#include <Kismet/GameplayStatics.h>
#include <Blueprint/UserWidget.h>
#include "FPPlayerController.h"

void AFPPlayerController::BeginPlay()
{
	crosshair = CreateWidget<UUserWidget>(this, crosshairWidget);
	crosshair->AddToViewport();
}

void AFPPlayerController::SetupInputComponent()
{
}




void AFPPlayerController::PlayerTick(float DeltaTime)
{
	Super::PlayerTick(DeltaTime);
}
