// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerCharacter.h"

// Sets default values
APlayerCharacter::APlayerCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void APlayerCharacter::BeginPlay()
{
	Super::BeginPlay();
	springArm = FindComponentByClass<USpringArmComponent>();

	originalSpringArmPos = springArm->TargetOffset;

}

// Called every frame
void APlayerCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	deltaTime = DeltaTime;

}

// Called to bind functionality to input
void APlayerCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	PlayerInputComponent->BindAction(TEXT("Sprint"), EInputEvent::IE_Pressed, this, &APlayerCharacter::SetSprinting);
	PlayerInputComponent->BindAction(TEXT("Sprint"), EInputEvent::IE_Released, this, &APlayerCharacter::SetWalking);
	PlayerInputComponent->BindAction(TEXT("EquipPrimary"), EInputEvent::IE_Pressed, this, &APlayerCharacter::EquipPrimary);
	PlayerInputComponent->BindAction(TEXT("EquipSecondary"), EInputEvent::IE_Pressed, this, &APlayerCharacter::EquipSecondary);
	PlayerInputComponent->BindAction(TEXT("Fire"), EInputEvent::IE_Pressed, this, &APlayerCharacter::FireWeapon);
	PlayerInputComponent->BindAction(TEXT("ADS"), EInputEvent::IE_Pressed, this, &APlayerCharacter::SetADSWeapon);
	PlayerInputComponent->BindAction(TEXT("ADS"), EInputEvent::IE_Released, this, &APlayerCharacter::SetHipfireWeapon);
	PlayerInputComponent->BindAction(TEXT("Reload"), EInputEvent::IE_Released, this, &APlayerCharacter::ReloadWeapon);

	PlayerInputComponent->BindAxis(TEXT("MoveVertical"), this, &APlayerCharacter::MoveVertical);
	PlayerInputComponent->BindAxis(TEXT("MoveHorizontal"), this, &APlayerCharacter::MoveHorizontal);
	PlayerInputComponent->BindAxis(TEXT("RotateHorizontal"), this, &APlayerCharacter::RotateHorizontal);
	PlayerInputComponent->BindAxis(TEXT("RotateVertical"), this, &APlayerCharacter::RotateVertical);
}

bool APlayerCharacter::IsWeaponEquiped()
{
	return (currentActiveGun != nullptr);
}

bool APlayerCharacter::IsAds()
{
	return (currentActiveGun && currentActiveGun->isAds);
}

bool APlayerCharacter::IsWalking()
{
	return (!isSprinting && GetVelocity().Size()>0) ;
}

int APlayerCharacter::GetWeaponCode()
{
	
	return (currentActiveGun)?currentActiveGun->itemCode:-1;
}

bool APlayerCharacter::IsShotgun()
{
	return (currentActiveGun && currentActiveGun->itemCode == 4);
}

int APlayerCharacter::GetReloadState()
{
	return (currentActiveGun && currentActiveGun->itemCode == 4)?currentActiveGun->reloadState : -1;
}

bool APlayerCharacter::IsSprinting()
{
	return (isSprinting && GetVelocity().Size() > 0);
}

bool APlayerCharacter::IsFiring()
{
	return (currentActiveGun && currentActiveGun->isFiring);
}

void APlayerCharacter::MoveVertical(float pValue)
{
	movementSpeed = (isSprinting && pValue >0) ? SPRINTING_SPEED : WALKING_SPEED;
	AddMovementInput(GetActorForwardVector() *movementSpeed * pValue * deltaTime);
}

void APlayerCharacter::MoveHorizontal(float pValue)
{
	AddMovementInput(GetActorRightVector() *WALKING_SPEED * pValue * deltaTime);
}

void APlayerCharacter::RotateHorizontal(float pValue)
{
	AddControllerYawInput(pValue);
}

void APlayerCharacter::RotateVertical(float pValue)
{
	AddControllerPitchInput(-pValue);
}

void APlayerCharacter::SetSprinting()
{
	isSprinting = true;
}

void APlayerCharacter::SetWalking()
{
	isSprinting = false;
}

void APlayerCharacter::SetCrouch()
{
	springArm->TargetOffset = originalSpringArmPos - FVector(0, 0, 50.f);
	isCrouch = true;
}

void APlayerCharacter::SetStanding()
{
	springArm->TargetOffset = originalSpringArmPos;
	isCrouch = false;
}

void APlayerCharacter::EquipPrimary()
{
	if(primaryWeapon)
		currentActiveGun = primaryWeapon;
}

void APlayerCharacter::EquipSecondary()
{
	if(secondaryWeapon)
		currentActiveGun = secondaryWeapon;
}

void APlayerCharacter::FireWeapon()
{
	if (currentActiveGun && currentActiveGun->CanFireWeapon())
	{
		currentActiveGun->FireWeapon();
	}
}

void APlayerCharacter::SetADSWeapon()
{
	if(currentActiveGun)
		currentActiveGun->SetADS();
}

void APlayerCharacter::SetHipfireWeapon()
{
	if(currentActiveGun)
		currentActiveGun->SetHipfire();
}

void APlayerCharacter::ReloadWeapon()
{
	if (currentActiveGun)
	{
		int needAmmo = currentActiveGun->maximumMagRounds - currentActiveGun->curMagRounds;

		//TODO: 체크 로직은 인벤토리가 추가되면 바로 바뀔 것
		if (currentActiveGun == primaryWeapon)
		{
			//needAmmo가 현재 보유 수보다 같거나 적고 현재 발사가 가능한 상태이면서 재장전 중이 아니면 재장전 아니면 빠꾸
			if (needAmmo <= ownedPrimaryWeaponAmmo && currentActiveGun->CanFireWeapon() && !currentActiveGun->isReloading)
			{
				currentActiveGun->Reload(needAmmo);
			}
		}
		else
		{
			//needAmmo가 현재 보유 수보다 같거나 적고 현재 발사가 가능한 상태이면서 재장전 중이 아니면 재장전 아니면 빠꾸
			if (needAmmo <= ownedSecondaryWeaponAmmo && currentActiveGun->CanFireWeapon() && !currentActiveGun->isReloading)
			{
				currentActiveGun->Reload(needAmmo);
			}
		}
	}
}
