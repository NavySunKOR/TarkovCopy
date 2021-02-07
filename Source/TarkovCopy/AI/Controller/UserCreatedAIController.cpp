// Fill out your copyright notice in the Description page of Project Settings.

#include <Components/SphereComponent.h>
#include <Components/PrimitiveComponent.h>
#include <BehaviorTree/BehaviorTree.h>
#include "UserCreatedAIController.h"



void AUserCreatedAIController::BeginPlay()
{
	RunBehaviorTree(blackboardTree);
}
