// Fill out your copyright notice in the Description page of Project Settings.

#include <Components/SphereComponent.h>
#include <TarkovCopy/Player/Character/PlayerCharacter.h>
#include <TarkovCopy/GameMode/TarkovCopyGameModeBase.h>
#include "AICharacter.h"

// Sets default values
AAICharacter::AAICharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
}

// Called when the game starts or when spawned
void AAICharacter::BeginPlay()
{
	Super::BeginPlay();
	ATarkovCopyGameModeBase* gameMode = GetWorld()->GetAuthGameMode<ATarkovCopyGameModeBase>();
	int totalCount = gameMode->allGunsInGame.Num();
	currentActiveGun = GetWorld()->SpawnActor<ABaseGun>(gameMode->allGunsInGame[0]);
	currentActiveGun->SetOwner(this);
	//TODO:캐릭터 손에 포지셔닝
	//currentActiveGun->AttachToComponent(armMesh, FAttachmentTransformRules::SnapToTargetIncludingScale, TEXT("weaponHolder"));
	//currentActiveGun->SetOwner(this);

	curHp = maxHp;
	
}

// Called every frame
void AAICharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void AAICharacter::TookDamage(float pDamageAmount, FHitResult pHitParts)
{
	//hitParts에 따라서 pDamageAmount를 계산할것.
	curHp -= pDamageAmount;
	if (curHp <= 0)
	{
		//TODO:PawnKilled 넣을것.
		curHp = 0;
	}
}

// Called to bind functionality to input
void AAICharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

void AAICharacter::NotifyActorBeginOverlap(AActor* Other)
{
	UE_LOG(LogTemp, Warning, TEXT("Copying!"));
	if (Other->ActorHasTag(FName("Player")))
	{
		UE_LOG(LogTemp, Warning, TEXT("Player!"));
		FVector targetDir = (Other->GetActorLocation() - GetOwner()->GetActorLocation());
		targetDir.Normalize();
		float angleCos = FVector::DotProduct(GetOwner()->GetActorForwardVector(), targetDir) / GetOwner()->GetActorForwardVector().Size() * targetDir.Size();
		float toAngle = FMath::RadiansToDegrees(FMath::Acos(angleCos));

		UE_LOG(LogTemp, Warning, TEXT("Angle! : %f"), toAngle);

		if (toAngle < 90.f)
		{
			outPlayerLocation = Other->GetActorLocation();
			outIsPlayerDetected = true;
		}
	}
}
void AAICharacter::NotifyActorEndOverlap(AActor* Other)
{
	if (Other->ActorHasTag(FName("Player")))
	{
		outIsPlayerDetected = false;
	}
}

void AAICharacter::FireWeapon()
{
	FVector start = GetActorLocation();
	FVector dir = (targetActor->GetActorLocation() - GetActorLocation());
	UE_LOG(LogTemp, Warning, TEXT("Firing"));
	currentActiveGun->FireWeapon(GetActorLocation(), dir.Rotation());
}
