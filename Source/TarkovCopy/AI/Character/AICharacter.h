// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include <Components/SphereComponent.h>
#include <TarkovCopy/Weapons/BaseGun.h>
#include "AICharacter.generated.h"

UCLASS()
class TARKOVCOPY_API AAICharacter : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AAICharacter();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	void TookDamage(float pDamageAmount, FHitResult pHitParts);

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
private:
	float maxHp = 100.f;
	float curHp;

	USphereComponent* detectTrigger;
	ABaseGun* currentActiveGun;

	virtual void NotifyActorBeginOverlap(AActor* Other) override;
	virtual void NotifyActorEndOverlap(AActor* Other) override;
public:
	FVector outPlayerLocation;
	bool outIsPlayerDetected = false;
	AActor* targetActor;


	void FireWeapon();
};
