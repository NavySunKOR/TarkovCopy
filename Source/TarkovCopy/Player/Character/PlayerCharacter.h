// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include <GameFramework/SpringArmComponent.h>
#include "TarkovCopy/InventoryAndItem/ItemInfos/ItemInfo.h"
#include "TarkovCopy/InventoryAndItem/GameFunctions/Inventory.h"
#include "TarkovCopy/Player/Controller/FPPlayerController.h"
#include "TarkovCopy/Weapons/BaseGun.h"
#include "PlayerCharacter.generated.h"

UCLASS()
class TARKOVCOPY_API APlayerCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	APlayerCharacter();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	float deltaTime = 0.f;
	USpringArmComponent* springArm;
	FVector originalSpringArmPos;
	AFPPlayerController* playerController;
	bool isSprinting = false;
	bool isCrouch = false;

	void MoveVertical(float pValue);
	void MoveHorizontal(float pValue);
	void RotateHorizontal(float pValue);
	void RotateVertical(float pValue);
	void SetSprinting();
	void SetWalking();
	void SetCrouch();
	void SetStanding();
	void EquipPrimary();
	void EquipSecondary();
	void FireWeapon();
	void SetADSWeapon();
	void SetHipfireWeapon();
	void ReloadWeapon();

	void Interact();
	void Inventory();



	ABaseGun* currentActiveGun;
	ABaseGun* primaryWeapon;
	ABaseGun* secondaryWeapon;

	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<ABaseGun> m416Origin;
	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<ABaseGun> m9Origin;

	UPROPERTY(EditAnywhere)
	int maxHp = 100;
	UPROPERTY(EditAnywhere)
	int curHp;


	UPROPERTY(EditAnywhere)
	float sprintingSpeed;
	UPROPERTY(EditAnywhere)
	float walkingSpeed;

	//TODO: 임시. 인벤토리 기능 추가시 변경 될 예정
	int ownedPrimaryWeaponAmmo; 
	int ownedSecondaryWeaponAmmo;


	UPROPERTY(EditAnywhere)
	TSubclassOf<UInventory> inventoryOrigin;


public:	

	UInventory* inventory;

	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	void TookDamage(float damage, FHitResult pHitParts);

	bool PickupItem(UItemInfo* pItemInfo);

//BlueprintPureOnly
protected:
	UFUNCTION(BlueprintPure)
    bool IsWeaponEquiped();
	UFUNCTION(BlueprintPure)
	bool IsAds();
	UFUNCTION(BlueprintPure)
	bool IsFiring();
	UFUNCTION(BlueprintPure)
	bool IsReloading();
	UFUNCTION(BlueprintPure)
	bool IsSprinting();
	UFUNCTION(BlueprintPure)
	bool IsWalking();
	UFUNCTION(BlueprintPure)
	int GetWeaponCode();

	//Shotgun only
	UFUNCTION(BlueprintPure)
	bool IsShotgun();
	UFUNCTION(BlueprintPure)
	int GetReloadState();

};
