// Fill out your copyright notice in the Description page of Project Settings.


#include "BaseGun.h"
#include <Runtime/Engine/Classes/Kismet/GameplayStatics.h>

// Sets default values
ABaseGun::ABaseGun()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	root = CreateDefaultSubobject<USceneComponent>("Root");
	SetRootComponent(root);
	gunMesh = CreateDefaultSubobject<USkeletalMeshComponent>("GunMesh");
	gunMesh->SetupAttachment(root);
}

// Called when the game starts or when spawned
void ABaseGun::BeginPlay()
{
	Super::BeginPlay();
	fireInterval = 60.f / rpm;
	curMagRounds = maximumMagRounds;
}

void ABaseGun::FireWeapon()
{
	curMagRounds--;
	isFiring = true;
	UGameplayStatics::SpawnSoundAttached(fireSound, gunMesh, TEXT("socketMuzzle"));
}

void ABaseGun::Reload(int pInsertMagazine)
{
	isReloading = true;
	tempInsertMag = pInsertMagazine;
}

void ABaseGun::SetADS()
{
	isAds = true;
}

void ABaseGun::SetHipfire()
{
	isAds = false;
}

//오버라이드 가능성 : 샷건(한발씩 장전되는데 바로 쏴야하므로
bool ABaseGun::CanFireWeapon()
{
	return (!isFiring || !isReloading) && curMagRounds > 0;
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

