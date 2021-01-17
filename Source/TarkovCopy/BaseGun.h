// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "BaseGun.generated.h"

UCLASS()
class TARKOVCOPY_API ABaseGun : public APawn
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	ABaseGun();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	int itemCode;
	int reloadState; //use for shotgun
	bool isAds;
	bool isFiring;
	bool isReloading;
	int maximumMagRounds;
	int curMagRounds;
	float damage;
	UPROPERTY(EditAnywhere)
	float rpm;
	float fireInterval;
	float fireTimer;

	virtual bool CanFireWeapon() const;
	virtual void FireWeapon();
	virtual void Reload(int pInsertMagazine);
	virtual void SetADS();
	virtual void SetHipfire();
	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
//BlueprintPures
protected: 
	UFUNCTION(BlueprintPure)
	bool IsReloading();
	UFUNCTION(BlueprintPure)
	bool IsFiring();


};
