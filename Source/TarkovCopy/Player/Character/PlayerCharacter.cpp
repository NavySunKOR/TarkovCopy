// Fill out your copyright notice in the Description page of Project Settings.

#include <GameFramework/CharacterMovementComponent.h>
#include "TarkovCopy/Interactable/InteractableObject.h"
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
	GetCharacterMovement()->MaxWalkSpeed = walkingSpeed;
	ownedPrimaryWeaponAmmo = 180;
	ownedSecondaryWeaponAmmo = 60;
	curHp = maxHp;

	springArm = FindComponentByClass<USpringArmComponent>();



	originalSpringArmPos = springArm->TargetOffset;
	TArray <USceneComponent*> childs;
	springArm->GetChildrenComponents(true, childs);
	USceneComponent* arm = nullptr;
	for (USceneComponent* comp : childs)
	{
		if (comp->GetName().Equals("FPArms"))
		{
			arm = comp;
			break;
		}
	}
	UE_LOG(LogTemp, Warning, TEXT("arm ? : %d"), arm);

	USkeletalMeshComponent* armMesh = nullptr;
	if (arm)
		armMesh = Cast<USkeletalMeshComponent>(arm);
	else
		return;
	UE_LOG(LogTemp, Warning, TEXT("ARM MESH? : %d"), armMesh);


	if (m416Origin)
	{
		primaryWeapon = GetWorld()->SpawnActor<ABaseGun>(m416Origin);
		primaryWeapon->AttachToComponent(armMesh, FAttachmentTransformRules::SnapToTargetIncludingScale, TEXT("weaponHolder"));
		primaryWeapon->SetOwner(this);
		primaryWeapon->SetActorRelativeLocation(primaryWeapon->playerPosition);
		primaryWeapon->SetActorRelativeRotation(primaryWeapon->playerRotation);
		primaryWeapon->SetActorRelativeScale3D(primaryWeapon->playerScale);
		UE_LOG(LogTemp, Warning, TEXT("M416"));
	}

	if (m9Origin)
	{
		secondaryWeapon = GetWorld()->SpawnActor<ABaseGun>(m9Origin);
		secondaryWeapon->AttachToComponent(armMesh, FAttachmentTransformRules::SnapToTargetIncludingScale, TEXT("weaponHolder"));
		secondaryWeapon->SetOwner(this);
		secondaryWeapon->SetActorRelativeLocation(secondaryWeapon->playerPosition);
		secondaryWeapon->SetActorRelativeRotation(secondaryWeapon->playerRotation);
		secondaryWeapon->SetActorRelativeScale3D(secondaryWeapon->playerScale);
		UE_LOG(LogTemp, Warning, TEXT("M9"));
	}
	EquipPrimary();


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
	PlayerInputComponent->BindAction(TEXT("Reload"), EInputEvent::IE_Pressed, this, &APlayerCharacter::ReloadWeapon);
	PlayerInputComponent->BindAction(TEXT("Crouch"), EInputEvent::IE_Pressed, this, &APlayerCharacter::SetCrouch);
	PlayerInputComponent->BindAction(TEXT("Crouch"), EInputEvent::IE_Released, this, &APlayerCharacter::SetStanding);
	PlayerInputComponent->BindAction(TEXT("Interact"), EInputEvent::IE_Pressed, this, &APlayerCharacter::Interact);

	PlayerInputComponent->BindAxis(TEXT("MoveVertical"), this, &APlayerCharacter::MoveVertical);
	PlayerInputComponent->BindAxis(TEXT("MoveHorizontal"), this, &APlayerCharacter::MoveHorizontal);
	PlayerInputComponent->BindAxis(TEXT("RotateHorizontal"), this, &APlayerCharacter::RotateHorizontal);
	PlayerInputComponent->BindAxis(TEXT("RotateVertical"), this, &APlayerCharacter::RotateVertical);
}

void APlayerCharacter::TookDamage(float damage, FHitResult pHitParts)
{
	UE_LOG(LogTemp, Warning, TEXT("Hag"));
	curHp -= damage;
	if (curHp <= 0)
	{
		UE_LOG(LogTemp, Warning, TEXT("Dead"));
		curHp = 0.f;
	}
}

bool APlayerCharacter::PickupItem(UItemInfo* pItemInfo)
{
	return inventory.AddItemToInventory(pItemInfo);
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
	return (currentActiveGun && currentActiveGun->itemCode == 3);
}

int APlayerCharacter::GetReloadState()
{
	return (currentActiveGun && currentActiveGun->itemCode == 3)?currentActiveGun->reloadState : -1;
}

bool APlayerCharacter::IsSprinting()
{
	return (isSprinting && GetVelocity().Size() > 0);
}

bool APlayerCharacter::IsFiring()
{
	return (currentActiveGun && currentActiveGun->isFiring);
}

bool APlayerCharacter::IsReloading()
{
	return (currentActiveGun && currentActiveGun->isReloading);
}

void APlayerCharacter::MoveVertical(float pValue)
{
	AddMovementInput(GetActorForwardVector() * 50.f * pValue * deltaTime);
}

void APlayerCharacter::MoveHorizontal(float pValue)
{
	AddMovementInput(GetActorRightVector() * 50.f * pValue * deltaTime);
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
	if (!isCrouch)
	{
		GetCharacterMovement()->MaxWalkSpeed = sprintingSpeed;
		isSprinting = true;
	}
}

void APlayerCharacter::SetWalking()
{
	GetCharacterMovement()->MaxWalkSpeed = walkingSpeed;
	isSprinting = false;
}

void APlayerCharacter::SetCrouch()
{
	if (IsSprinting())
	{
		SetWalking();
	}
	Crouch();
	//springArm->TargetOffset = originalSpringArmPos - FVector(0, 0, 500.f);
	isCrouch = true;
}

void APlayerCharacter::SetStanding()
{
	UnCrouch();
	//springArm->TargetOffset = originalSpringArmPos;
	isCrouch = false;
}

void APlayerCharacter::EquipPrimary()
{
	if (primaryWeapon)
	{
		primaryWeapon->SetActorHiddenInGame(false);
		primaryWeapon->SetActorEnableCollision(true);
		primaryWeapon->SetActorTickEnabled(true);
		currentActiveGun = primaryWeapon;
	
		if (secondaryWeapon)
		{
			secondaryWeapon->SetActorHiddenInGame(true);
			secondaryWeapon->SetActorEnableCollision(false);
			secondaryWeapon->SetActorTickEnabled(false);
		}
	}
}

void APlayerCharacter::EquipSecondary()
{
	if (secondaryWeapon)
	{
		secondaryWeapon->SetActorHiddenInGame(false);
		secondaryWeapon->SetActorEnableCollision(true);
		secondaryWeapon->SetActorTickEnabled(true);
		currentActiveGun = secondaryWeapon;
		if (primaryWeapon)
		{
			primaryWeapon->SetActorHiddenInGame(true);
			primaryWeapon->SetActorEnableCollision(false);
			primaryWeapon->SetActorTickEnabled(false);
		}
	}
}

void APlayerCharacter::FireWeapon()
{
	if (currentActiveGun && currentActiveGun->CanFireWeapon())
	{
		FVector start;
		FRotator dir;
		GetController()->GetPlayerViewPoint(start, dir);
		currentActiveGun->FireWeapon(start,dir);
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
		int ownedAmmo = (currentActiveGun == primaryWeapon) ? ownedPrimaryWeaponAmmo : ownedSecondaryWeaponAmmo;

		//TODO: 체크 로직은 인벤토리가 추가되면 바로 바뀔 것
		//needAmmo가 현재 보유 수보다 같거나 적고 현재 발사가 가능한 상태이면서 재장전 중이 아니면 재장전 아니면 빠꾸
		UE_LOG(LogTemp, Warning, TEXT("Reload"));
		if (needAmmo > 0 && needAmmo <= ownedAmmo && !currentActiveGun->isReloading)
		{
			UE_LOG(LogTemp, Warning, TEXT("Reload Actual"));
			currentActiveGun->Reload(needAmmo);
			if (currentActiveGun == primaryWeapon)
			{
				ownedPrimaryWeaponAmmo -= needAmmo;
			}
			else
			{
				ownedSecondaryWeaponAmmo -= needAmmo;
			}
		}
	}
}

void APlayerCharacter::Interact()
{
	FHitResult hit;
	FVector start;
	FRotator dir;
	FCollisionQueryParams param;
	param.AddIgnoredActor(this);

	APlayerController* con = Cast<APlayerController>(GetController());
	if (con == nullptr)
		return;
	con->GetPlayerViewPoint(start, dir);

	if (GetWorld()->LineTraceSingleByChannel(hit, start, start + dir.Vector() * 800.f, ECollisionChannel::ECC_Pawn, param))
	{

		UE_LOG(LogTemp, Warning, TEXT("Tesst : %s"), *hit.Actor->GetName());
		AInteractableObject* inter = Cast<AInteractableObject>(hit.GetActor());
		if (inter != nullptr)
		{
			UE_LOG(LogTemp, Warning, TEXT("Interacting"));
			inter->Interact();
		}
	}
}
