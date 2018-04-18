// Fill out your copyright notice in the Description page of Project Settings.

#include "GuestAIController.h"
#include "Kismet/GameplayStatics.h"
#include "Navigation/CrowdFollowingComponent.h"
#include "BehaviorTree/BehaviorTreeComponent.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "BehaviorTree/BehaviorTree.h"
#include "Guest.h"
#include "Waypoint.h"

AGuestAIController::AGuestAIController(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer.SetDefaultSubobjectClass<UCrowdFollowingComponent>(TEXT("PathFollowingComponent")))
{
	BlackboardComp = CreateDefaultSubobject<UBlackboardComponent>(TEXT("Blackboard component"));
	BehaviorComp = CreateDefaultSubobject<UBehaviorTreeComponent>(TEXT("Behavior component"));
}

void AGuestAIController::BeginPlay()
{
	Super::BeginPlay();

	TArray<AActor*> actors;
	UGameplayStatics::GetAllActorsOfClass(this, AWaypoint::StaticClass(), actors);
	for (AActor* actor : actors) {
		AWaypoint* waypoint = Cast<AWaypoint>(actor);
		Waypoints.Add(waypoint);
	}

	// TODO: Specify the start waypoint in the editor
	TargetWaypoint = Waypoints[0];
}


void AGuestAIController::Possess(APawn* InPawn)
{
	Super::Possess(InPawn);

	AGuest* guest = Cast<AGuest>(InPawn);
	if (guest) {
		UBehaviorTree* behavior = guest->GetBehavior();
		if (behavior) {
			BlackboardComp->InitializeBlackboard(*(behavior->BlackboardAsset));
			// Grab key id
			TargetLocationKeyID = BlackboardComp->GetKeyID("TargetLocation");
			BehaviorComp->StartTree(*behavior);
		}
	}

}

AWaypoint* AGuestAIController::NextTargetWaypoint()
{
	AWaypoint* target = TargetWaypoint->GetNextRandomWaypoint(PreviousWaypoint);
	PreviousWaypoint = TargetWaypoint;
	TargetWaypoint = target;

	return TargetWaypoint;
}


AWaypoint* AGuestAIController::GetTargetWaypoint()
{
	return TargetWaypoint;
}

AWaypoint* AGuestAIController::GetPrviousWaypoint()
{
	return PreviousWaypoint;
}