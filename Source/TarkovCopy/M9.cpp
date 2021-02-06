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

	//TODO: �����̾�� �ƴϸ� ads�Ŀ� ���� �߻� ����� �ٸ��� �ϰ�, ads���� �߻�� �ѱ�� ���� ������� �ݵ��� ����(���Ⱑ ���� �ö󰡾���);
	if (GetWorld()->LineTraceSingleByChannel(hit, start, start + dir.Vector() * range, ECollisionChannel::ECC_Pawn, param))
	{
		//���� hit�� ĳ���͸�
		AAICharacter* aiCharacter = Cast<AAICharacter>(hit.GetActor());
		if (aiCharacter != nullptr)
		{
			aiCharacter->TookDamage(damage, hit);
		}
		//�ƴϸ� ����ó��.
		else
		{
			//TODO: ���߿� ������ �ڵ带 �����ϰ� �ش� ��ҿ� ������ Ƣ��� ������� �����Ұ�.
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
