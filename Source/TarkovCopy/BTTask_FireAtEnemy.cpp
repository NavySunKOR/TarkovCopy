// Fill out your copyright notice in the Description page of Project Settings.

#include "AICharacter.h"
#include <AIController.h>
#include <BehaviorTree/BehaviorTreeComponent.h>
#include <BehaviorTree/BlackboardComponent.h>
#include "BTTask_FireAtEnemy.h"


EBTNodeResult::Type UBTTask_FireAtEnemy::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	AAICharacter* aiCharacter = Cast<AAICharacter>(OwnerComp.GetAIOwner()->GetPawn());
	
	OwnerComp.GetAIOwner()->SetFocus(aiCharacter->targetActor,EAIFocusPriority::Gameplay);

	if (aiCharacter == nullptr)
	{
		return EBTNodeResult::Failed;
	}

	return EBTNodeResult::Succeeded;
}