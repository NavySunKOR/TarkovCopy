// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "InteractableObject.h"
#include "ExfilRoute.generated.h"

/**
 * 
 */
UCLASS()
class TARKOVCOPY_API AExfilRoute : public AInteractableObject
{
	GENERATED_BODY()

public:
	virtual void Interact() override;
};
