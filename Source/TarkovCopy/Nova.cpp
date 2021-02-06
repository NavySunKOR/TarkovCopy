// Fill out your copyright notice in the Description page of Project Settings.


#include "Nova.h"

void ANova::BeginPlay()
{
    Super::BeginPlay();
}

bool ANova::CanFireWeapon()
{
    return false;
}

void ANova::FireWeapon(FVector start, FRotator dir)
{
}

void ANova::Reload(int pInsertMagazine)
{
}

void ANova::SetADS()
{
}

void ANova::SetHipfire()
{
}

void ANova::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);
}
