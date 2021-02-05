// Fill out your copyright notice in the Description page of Project Settings.

#include "AICharacter.h"
#include <AIController.h>
#include <BehaviorTree/BlackboardComponent.h>
#include "BTDecorator_IsInDetectRange.h"

bool UBTDecorator_IsInDetectRange::CalculateRawConditionValue(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) const
{
	//Super::WrappedCanExecute(OwnerComp, NodeMemory);

	AAICharacter* owner = Cast<AAICharacter>(OwnerComp.GetAIOwner()->GetPawn());
	if (owner == nullptr)
	{
		UE_LOG(LogTemp, Warning, TEXT("Failed to cast in detect range"));
		return false;
	}



	if (!owner->outIsPlayerDetected)
	{
		UE_LOG(LogTemp, Warning, TEXT("detect range returns false"));
		return false;
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("detect range returns true"));
		return true;
	}
}