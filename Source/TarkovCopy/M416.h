// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BaseGun.h"
#include "M416.generated.h"

/**
 * 
 */
UCLASS()
class TARKOVCOPY_API AM416 : public ABaseGun
{
	GENERATED_BODY()
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
public:
	virtual bool CanFireWeapon() override;
	virtual void FireWeapon() override;
	virtual void Reload(int pInsertMagazine) override;
	virtual void SetADS() override;
	virtual void SetHipfire() override;
	virtual void Tick(float DeltaTime) override;
};
