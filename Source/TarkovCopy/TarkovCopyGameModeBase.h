// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "TarkovCopy/InteractableObject.h"
#include "TarkovCopyGameModeBase.generated.h"

/**
 * 
 */
UCLASS()
class TARKOVCOPY_API ATarkovCopyGameModeBase : public AGameModeBase
{
	GENERATED_BODY()

public:
	virtual void QuestCompleted(AInteractableObject* questItem);
	virtual void TryExfil();

};
