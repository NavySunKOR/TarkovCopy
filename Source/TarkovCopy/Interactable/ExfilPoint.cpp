// Fill out your copyright notice in the Description page of Project Settings.


#include "ExfilPoint.h"
#include <Kismet/GameplayStatics.h>
#include <TarkovCopy/GameMode/EscapeGameMode.h>

// Sets default values for this component's properties
UExfilPoint::UExfilPoint()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UExfilPoint::BeginPlay()
{
	Super::BeginPlay();
	// ...
	playerPawn = UGameplayStatics::GetPlayerPawn(GetWorld(), 0);
	FScriptDelegate exfilingDelegate = FScriptDelegate();
	FScriptDelegate cancelExfilingDelegate = FScriptDelegate();
	exfilingDelegate.BindUFunction(this, "Exfiling");
	cancelExfilingDelegate.BindUFunction(this, "CancelExfiling");
	trigger->OnActorBeginOverlap.Add(exfilingDelegate);
	trigger->OnActorEndOverlap.Add(cancelExfilingDelegate);
}


// Called every frame
void UExfilPoint::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

void UExfilPoint::Exfiling()
{
	GetWorld()->GetAuthGameMode<AEscapeGameMode>()->TryExfil();
}

void UExfilPoint::CancelExfiling()
{
	GetWorld()->GetAuthGameMode<AEscapeGameMode>()->CancelExfil();
}

