// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include <GameFramework/SpringArmComponent.h>
#include <TarkovCopy/BaseGun.h>
#include "PlayerCharacter.generated.h"
#define SPRINTING_SPEED 400.f
#define WALKING_SPEED 100.f

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
	float movementSpeed = WALKING_SPEED;
	USpringArmComponent* springArm;
	FVector originalSpringArmPos;
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

	ABaseGun* currentActiveGun;
	ABaseGun* primaryWeapon;
	ABaseGun* secondaryWeapon;

	//TODO: 임시. 인벤토리 기능 추가시 변경 될 예정
	int ownedPrimaryWeaponAmmo; 
	int ownedSecondaryWeaponAmmo;


public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
	
};
