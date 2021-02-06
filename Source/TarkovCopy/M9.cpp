// Fill out your copyright notice in the Description page of Project Settings.


#include <Kismet/GameplayStatics.h>
#include "M9.h"
#include "TarkovCopy/AICharacter.h"

void AM9::BeginPlay()
{
	itemCode = 0;
	maximumMagRounds = 15;
	reloadInterval = 3.f;
	rpm = 55.f;
	damage = 15.f;
	range = 15000.f;
	playerScale = FVector(1.25f, 1.25f, 1.25f);
	playerRotation = FRotator(4.f, 77.f, 11.f);
	playerPosition = FVector(-10.f, 3.4f, -3.5f);
	Super::BeginPlay();
}

bool AM9::CanFireWeapon()
{
	return Super::CanFireWeapon();
}

void AM9::FireWeapon(FVector start, FRotator dir)
{
	FHitResult hit;
	FCollisionQueryParams param;
	param.AddIgnoredActor(this);
	APawn* player = Cast<APawn>(GetOwner());
	param.AddIgnoredActor(player);

	//TODO: 힙파이어냐 아니면 ads냐에 따라서 발사 방식을 다르게 하고, ads에서 발사시 총기는 선형 방식으로 반동을 적용(무기가 위로 올라가야함);
	if (GetWorld()->LineTraceSingleByChannel(hit, start, start + dir.Vector() * range, ECollisionChannel::ECC_Pawn, param))
	{
		//맞은 hit가 캐릭터면
		AAICharacter* aiCharacter = Cast<AAICharacter>(hit.GetActor());
		if (aiCharacter != nullptr)
		{
			aiCharacter->TookDamage(damage, hit);
		}
		//아니면 지형처리.
		else
		{
			//TODO: 나중에 지형에 코드를 삽입하고 해당 장소에 파편을 튀기는 방식으로 제작할것.
			UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), hitTerrain, hit.ImpactPoint, dir, true);
		}
	}
	Super::FireWeapon(start,dir);
}

void AM9::Reload(int pInsertMagazine)
{
	Super::Reload(pInsertMagazine);
}

void AM9::SetADS()
{
	isAds = true;
}

void AM9::SetHipfire()
{
	isAds = false;
}

void AM9::Tick(float DeltaTime)
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
			curMagRounds += tempInsertMag;
			isReloading = false;
			reloadTimer = 0.f;
		}
	}
}
