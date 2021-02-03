// Fill out your copyright notice in the Description page of Project Settings.


#include "UserCreatedAIController.h"

void AUserCreatedAIController::BeginPlay()
{
	RunBehaviorTree(blackboardTree);
}