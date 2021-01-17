// Fill out your copyright notice in the Description page of Project Settings.


#include "BaseGun.h"

// Sets default values
ABaseGun::ABaseGun()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void ABaseGun::BeginPlay()
{
	Super::BeginPlay();
	fireInterval = 60.f / rpm;
}

void ABaseGun::FireWeapon()
{
	curMagRounds--;
	isFiring = true;
}

void ABaseGun::Reload(int pInsertMagazine)
{
}

void ABaseGun::SetADS()
{
	isAds = true;
}

void ABaseGun::SetHipfire()
{
	isAds = false;
}

bool ABaseGun::CanFireWeapon() const
{
	return !isFiring || !isReloading;
}

// Called every frame
void ABaseGun::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void ABaseGun::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

bool ABaseGun::IsReloading()
{
	return isReloading;
}

bool ABaseGun::IsFiring()
{
	return isFiring;
}

