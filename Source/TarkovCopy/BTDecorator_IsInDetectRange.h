// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTDecorator.h"
#include "BTDecorator_IsInDetectRange.generated.h"

/**
 * 
 */
UCLASS()
class TARKOVCOPY_API UBTDecorator_IsInDetectRange : public UBTDecorator
{
	GENERATED_BODY()
private:
	virtual bool CalculateRawConditionValue(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) const override;
};
