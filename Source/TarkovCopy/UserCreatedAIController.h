// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "UserCreatedAIController.generated.h"

/**
 * 
 */
UCLASS()
class TARKOVCOPY_API AUserCreatedAIController : public AAIController
{
	GENERATED_BODY()


protected:
	virtual void BeginPlay() override;
public:
	UPROPERTY(EditAnywhere)
	UBehaviorTree* blackboardTree;


};