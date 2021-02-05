// Fill out your copyright notice in the Description page of Project Settings.

#include "AICharacter.h"
#include <AIController.h>
#include <BehaviorTree/BlackboardComponent.h>
#include "BTTask_SearchEnemy.h"

EBTNodeResult::Type UBTTask_SearchEnemy::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	AAICharacter* owner = Cast<AAICharacter>(OwnerComp.GetAIOwner()->GetPawn());
	if (owner == nullptr)
	{
		UE_LOG(LogTemp, Warning, TEXT("Failed to cast"));
		return EBTNodeResult::Failed;
	}
	UBlackboardComponent* blackboard = OwnerComp.GetBlackboardComponent();

	if (owner->outIsPlayerDetected)
	{
		blackboard->SetValueAsVector(TEXT("LastPlayerLocation"), owner->outPlayerLocation);
		blackboard->SetValueAsBool(TEXT("IsPlayerContacted"), owner->outIsPlayerDetected);
	}

	return EBTNodeResult::Succeeded;
}
