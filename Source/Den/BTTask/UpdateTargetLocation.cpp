// Fill out your copyright notice in the Description page of Project Settings.

#include "UpdateTargetLocation.h"
#include "../GuestAIController.h"
#include "../Waypoint.h"
#include "AI/Navigation/NavigationSystem.h"
#include "BehaviorTree/Blackboard/BlackboardKeyAllTypes.h"
#include "BehaviorTree/BehaviorTreeComponent.h"

EBTNodeResult::Type UUpdateTargetLocation::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	AGuestAIController* controller = Cast<AGuestAIController>(OwnerComp.GetAIOwner());
	if (controller) {
		AWaypoint* targetWaypoint = controller->GetTargetWaypoint();
		FVector location = UNavigationSystem::GetRandomReachablePointInRadius(controller, targetWaypoint->GetActorLocation(), targetWaypoint->GetRadius());
		OwnerComp.GetBlackboardComponent()->SetValue<UBlackboardKeyType_Vector>(controller->TargetLocationKeyID, location);
	}
	return EBTNodeResult::Succeeded;
}