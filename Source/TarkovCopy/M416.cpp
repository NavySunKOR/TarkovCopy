// Fill out your copyright notice in the Description page of Project Settings.


#include <Kismet/GameplayStatics.h>
#include "M416.h"

void AM416::BeginPlay()
{
	itemCode = 5;
	maximumMagRounds = 30;
	rpm = 750.f;
	damage = 25.f;
	range = 300.f;
	Super::BeginPlay();

}

bool AM416::CanFireWeapon()
{
	return Super::CanFireWeapon();
}


void AM416::FireWeapon()
{
	FHitResult hit;
	FVector start;
	FRotator dir;
	FCollisionQueryParams param;
	param.AddIgnoredActor(this);
	param.AddIgnoredActor(UGameplayStatics::GetPlayerPawn(GetWorld(), 0));
	GetController()->GetPlayerViewPoint(start, dir);
	
	if (GetWorld()->LineTraceSingleByChannel(hit, start, start + dir.Vector() * range, ECollisionChannel::ECC_EngineTraceChannel1, param))
	{
		//맞은 hit가 캐릭터면

		//아니면 지형처리.
	}
	Super::FireWeapon();

}

void AM416::Reload(int pInsertMagazine)
{
}

void AM416::SetADS()
{
}

void AM416::SetHipfire()
{
}

void AM416::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);
	if (isFiring)
	{
		fireTimer += DeltaTime;
		if (fireTimer > fireInterval)
		{
			isFiring = false;
			fireTimer = 0.f;

		}
	}

	if (isReloading)
	{
		reloadTimer += DeltaTime;
		if (reloadTimer > reloadInterval)
		{
			isReloading = false;
			reloadTimer = 0.f;
		}
	}
}
