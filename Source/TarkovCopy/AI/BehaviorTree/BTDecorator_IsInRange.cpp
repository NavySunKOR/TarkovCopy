// Fill out your copyright notice in the Description page of Project Settings.

#include "TarkovCopy/AI/Character/AICharacter.h"
#include <AIController.h>
#include <BehaviorTree/BlackboardComponent.h>
#include "BTDecorator_IsInRange.h"


bool UBTDecorator_IsInRange::CalculateRawConditionValue(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) const
{
	Super::CalculateRawConditionValue(OwnerComp, NodeMemory);
	AAICharacter* owner = Cast<AAICharacter>(OwnerComp.GetAIOwner()->GetPawn());
	if (owner == nullptr)
	{
		UE_LOG(LogTemp, Warning, TEXT("Failed to cast"));
		return false;
	}

	FVector startPos = owner->GetActorLocation();
	FVector dir = owner->outPlayerLocation -  owner->GetActorLocation();
	FHitResult hit;
	FCollisionQueryParams CollisionParams;
	CollisionParams.AddIgnoredActor(owner);

	if (!owner->outIsPlayerDetected)
		return false;
	else
	{
		if (GetWorld()->LineTraceSingleByChannel(hit, startPos, dir * 1000.f, ECollisionChannel::ECC_Pawn, CollisionParams))
		{
			if (hit.Actor->ActorHasTag(TEXT("Player")))
			{
				UE_LOG(LogTemp, Warning, TEXT("in range returns true"));
				owner->targetActor = hit.Actor.Get();
				return true;
			}
			else
			{
				UE_LOG(LogTemp, Warning, TEXT("in range returns false"));
				owner->targetActor = nullptr;
				return false;
			}
		}
		else
		{
			//UE_LOG(LogTemp, Warning, TEXT("in range returns doesn't hit"));
			owner->targetActor = nullptr;
			return false;
		}
	}
}
