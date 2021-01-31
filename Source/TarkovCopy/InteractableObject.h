// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "InteractableObject.generated.h"


UCLASS( )
class TARKOVCOPY_API AInteractableObject : public AActor
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	AInteractableObject();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

public:
	virtual void Interact();
		
};
