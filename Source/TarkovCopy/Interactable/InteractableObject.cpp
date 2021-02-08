// Fill out your copyright notice in the Description page of Project Settings.

#include <Kismet/GameplayStatics.h>
#include <TarkovCopy/Player/Character/PlayerCharacter.h>
#include "InteractableObject.h"

// Sets default values for this component's properties
AInteractableObject::AInteractableObject()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryActorTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void AInteractableObject::BeginPlay()
{

	// ...
	Super::BeginPlay();
	playerCharacter = Cast<APlayerCharacter>(UGameplayStatics::GetPlayerPawn(GetWorld(), 0));
}


// Called every frame
void AInteractableObject::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	// ...
}

void AInteractableObject::Interact()
{
	
}

