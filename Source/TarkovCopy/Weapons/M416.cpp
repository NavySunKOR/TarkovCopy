// Fill out your copyright notice in the Description page of Project Settings.


#include <Kismet/GameplayStatics.h>
#include "TarkovCopy/AI/Character/AICharacter.h"
#include "TarkovCopy/Player/Character/PlayerCharacter.h"
#include "M416.h"

void AM416::BeginPlay()
{
	itemCode = 4;
	maximumMagRounds = 30;
	reloadInterval = 5.f;
	rpm = 750.f;
	damage = 25.f;
	range = 15000.f;
	playerScale = FVector(1.25f,1.25f, 1.25f);
	playerRotation = FRotator(3.f, 90.f, 15.f);
	playerPosition = FVector(-5.6f, 4.0f, -3.2f);
	Super::BeginPlay();

}

bool AM416::CanFireWeapon()
{
	return Super::CanFireWeapon();
}


void AM416::FireWeapon(FVector start,FRotator dir)
{
	FHitResult hit;
	FCollisionQueryParams param;

	GetWorld()->DebugDrawTraceTag = FName("Cong");
	param.AddIgnoredActor(this);
	APawn* player = Cast<APawn>(GetOwner());
	UE_LOG(LogTemp, Warning, TEXT("Owner thing : %s"), *player->GetName());
	param.AddIgnoredActor(player);
	param.TraceTag = FName("Cong");

	//TODO: �����̾�� �ƴϸ� ads�Ŀ� ���� �߻� ����� �ٸ��� �ϰ�, ads���� �߻�� �ѱ�� ���� ������� �ݵ��� ����(���Ⱑ ���� �ö󰡾���);
	if (GetWorld()->LineTraceSingleByChannel(hit, start, start + dir.Vector() * range, ECollisionChannel::ECC_Pawn , param))
	{
		UE_LOG(LogTemp, Warning, TEXT("Hit something : %s"), *hit.GetActor()->GetName());
		//���� hit�� ĳ���͸�
		AAICharacter* aiCharacter = Cast<AAICharacter>(hit.GetActor());
		APlayerCharacter* playerCharacter = Cast<APlayerCharacter>(hit.GetActor());
		if (aiCharacter != nullptr)
		{
			UE_LOG(LogTemp, Warning, TEXT("NAME : %s"), *aiCharacter->GetName());
			aiCharacter->TookDamage(damage, hit);
		}
		//�ƴϸ� ����ó��.
		else if (playerCharacter != nullptr)
		{
			UE_LOG(LogTemp, Warning, TEXT("Hit player"));
			playerCharacter->TookDamage(damage, hit);
		}
		else
		{
			//TODO: ���߿� ������ �ڵ带 �����ϰ� �ش� ��ҿ� ������ Ƣ��� ������� �����Ұ�.
			UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), hitTerrain, hit.ImpactPoint, dir);
		}
	}
	Super::FireWeapon(start, dir);

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
