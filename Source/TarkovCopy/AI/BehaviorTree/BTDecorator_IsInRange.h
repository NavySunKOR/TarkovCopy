// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTDecorator.h"
#include "BTDecorator_IsInRange.generated.h"

/**
 * 
 */
UCLASS()
class TARKOVCOPY_API UBTDecorator_IsInRange : public UBTDecorator
{
	GENERATED_BODY()
private:
	virtual bool CalculateRawConditionValue(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) const override;
};
