// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Waypoint.generated.h"

UCLASS()
class DEN_API AWaypoint : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AWaypoint();

protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TArray<AWaypoint*> Links;

	UPROPERTY(VisibleAnywhere)
	class UBillboardComponent* billboardComp;

	// Visual indication only, not used in runtime.
	UPROPERTY(VisibleAnywhere)
	class USphereComponent* SphereComp;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Waypoint")
	float Radius;

public:	
	UFUNCTION(BlueprintPure, Category = "Waypoint")
	TArray<AWaypoint*> GetLinks();

	UFUNCTION(BlueprintCallable, Category = "Waypoint")
	virtual AWaypoint* GetNextRandomWaypoint(AWaypoint* previousWaypoint);

	// Handles editor radius update, then update sphere visual indication
	virtual void PostEditChangeProperty(FPropertyChangedEvent& e) override;

	float GetRadius();
};
