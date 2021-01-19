// Fill out your copyright notice in the Description page of Project Settings.


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
		curHp = 0;
		//TODO:PawnKilled 넣을것.
	}
}

// Called to bind functionality to input
void AAICharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

