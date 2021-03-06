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

	//TODO: 힙파이어냐 아니면 ads냐에 따라서 발사 방식을 다르게 하고, ads에서 발사시 총기는 선형 방식으로 반동을 적용(무기가 위로 올라가야함);
	if (GetWorld()->LineTraceSingleByChannel(hit, start, start + dir.Vector() * range, ECollisionChannel::ECC_Pawn , param))
	{
		UE_LOG(LogTemp, Warning, TEXT("Hit something : %s"), *hit.GetActor()->GetName());
		//맞은 hit가 캐릭터면
		AAICharacter* aiCharacter = Cast<AAICharacter>(hit.GetActor());
		APlayerCharacter* playerCharacter = Cast<APlayerCharacter>(hit.GetActor());
		if (aiCharacter != nullptr)
		{
			UE_LOG(LogTemp, Warning, TEXT("NAME : %s"), *aiCharacter->GetName());
			aiCharacter->TookDamage(damage, hit);
		}
		//아니면 지형처리.
		else if (playerCharacter != nullptr)
		{
			UE_LOG(LogTemp, Warning, TEXT("Hit player"));
			playerCharacter->TookDamage(damage, hit);
		}
		else
		{
			//TODO: 나중에 지형에 코드를 삽입하고 해당 장소에 파편을 튀기는 방식으로 제작할것.
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
