// Fill out your copyright notice in the Description page of Project Settings.


#include <Kismet/GameplayStatics.h>
#include "M416.h"
#include "TarkovCopy/AICharacter.h"

void AM416::BeginPlay()
{
	itemCode = 4;
	maximumMagRounds = 30;
	reloadInterval = 5.f;
	rpm = 750.f;
	damage = 25.f;
	range = 15000.f;
	fppScale = FVector(1.25f,1.25f, 1.25f);
	fppRotation = FRotator(3.f, 90.f, 15.f);
	fppPosition = FVector(-5.6f, 4.0f, -3.2f);
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
	APawn* player = Cast<APawn>(GetOwner());
	if (player != nullptr)
	{
		AController* playCon = player->GetController();
		if (playCon != nullptr)
		{

			playCon->GetPlayerViewPoint(start, dir);
		}
		else
		{
			return;
		}
	}
	else
	{
		return;
	}

	
	//TODO: �����̾�� �ƴϸ� ads�Ŀ� ���� �߻� ����� �ٸ��� �ϰ�, ads���� �߻�� �ѱ�� ���� ������� �ݵ��� ����(���Ⱑ ���� �ö󰡾���);
	if (GetWorld()->LineTraceSingleByChannel(hit, start, start + dir.Vector() * range, ECollisionChannel::ECC_Pawn , param))
	{
		//���� hit�� ĳ���͸�
		AAICharacter* aiCharacter = Cast<AAICharacter>(hit.GetActor());
		if (aiCharacter != nullptr)
		{
			UE_LOG(LogTemp, Warning, TEXT("NAME : %s"), *aiCharacter->GetName());
			aiCharacter->TookDamage(damage, hit);
		}
		//�ƴϸ� ����ó��.
		else
		{
			//TODO: ���߿� ������ �ڵ带 �����ϰ� �ش� ��ҿ� ������ Ƣ��� ������� �����Ұ�.
			UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), hitTerrain, hit.ImpactPoint, dir);
		}
	}
	Super::FireWeapon();

}

void AM416::Reload(int pInsertMagazine)
{
	Super::Reload(pInsertMagazine);
}

void AM416::SetADS()
{
	isAds = true;
}

void AM416::SetHipfire()
{
	isAds = false;
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
			curMagRounds += tempInsertMag;
			isReloading = false;
			reloadTimer = 0.f;
		}
	}
}
