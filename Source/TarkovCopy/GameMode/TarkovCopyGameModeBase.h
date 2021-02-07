// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "TarkovCopy/Interactable/InteractableObject.h"
#include <TarkovCopy/Weapons/BaseGun.h>
#include "TarkovCopyGameModeBase.generated.h"

/**
 * 
 */
UCLASS()
class TARKOVCOPY_API ATarkovCopyGameModeBase : public AGameModeBase
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere)
	TArray<TSubclassOf<ABaseGun>> allGunsInGame;

	virtual void QuestCompleted(AInteractableObject* questItem);
	virtual void TryExfil();
	virtual void CancelExfil();

};
