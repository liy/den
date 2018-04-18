// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "GuestAIController.generated.h"

class AWaypoint;

/**
 * 
 */
UCLASS()
class DEN_API AGuestAIController : public AAIController
{
	GENERATED_BODY()


public:
	AGuestAIController(const FObjectInitializer& ObjectInitializer = FObjectInitializer::Get());

	UFUNCTION(BlueprintCallable, Category = "Waypoint")
	AWaypoint* NextTargetWaypoint();

	UFUNCTION(Blueprintpure, Category = "Waypoint")
	AWaypoint* GetTargetWaypoint();

	UFUNCTION(Blueprintpure, Category = "Waypoint")
	AWaypoint* GetPrviousWaypoint();

	virtual void Possess(APawn* InPawn) override;

	// For behaviour tree
	uint8 TargetLocationKeyID;
	
private:
	TArray<AWaypoint*> Waypoints;

protected:
	UPROPERTY(transient)
	class UBlackboardComponent* BlackboardComp;

	UPROPERTY(transient)
	class UBehaviorTreeComponent* BehaviorComp;

	AWaypoint* TargetWaypoint;

	AWaypoint* PreviousWaypoint;

	/** Overridable native event for when play begins for this actor. */
	virtual void BeginPlay() override;
};