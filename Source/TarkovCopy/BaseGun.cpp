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
	
}

void ABaseGun::FireWeapon()
{

}

void ABaseGun::Reload(int pInsertMagazine)
{
}

void ABaseGun::SetADS()
{
}

void ABaseGun::SetHipfire()
{
}

bool ABaseGun::CanFireWeapon() const
{

	return false;
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

