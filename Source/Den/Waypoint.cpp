// Fill out your copyright notice in the Description page of Project Settings.

#include "Waypoint.h"
#include "Components/SphereComponent.h"
#include "Components/BillboardComponent.h"

// Sets default values
AWaypoint::AWaypoint()
{
	Radius = 50.0f;

	RootComponent = CreateDefaultSubobject<USceneComponent>(TEXT("Scene"));

	billboardComp = CreateDefaultSubobject<UBillboardComponent>(TEXT("Billboard"));
	billboardComp->AttachToComponent(RootComponent, FAttachmentTransformRules::KeepRelativeTransform);

	SphereComp = CreateDefaultSubobject<USphereComponent>(TEXT("Waypoint Sphere"));
	SphereComp->SetSphereRadius(Radius);
	SphereComp->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	SphereComp->AttachToComponent(RootComponent, FAttachmentTransformRules::KeepRelativeTransform);
}


TArray<AWaypoint*> AWaypoint::GetLinks() 
{
	return Links;
}


AWaypoint* AWaypoint::GetNextRandomWaypoint(AWaypoint* previousWaypoint)
{
	if (Links.Num() == 1) return Links[0];

	TArray<AWaypoint*> pool = Links.FilterByPredicate([&](const AWaypoint* waypoint) -> bool {
		return waypoint != previousWaypoint;
	});

	return pool[FMath::RandRange(0, pool.Num()-1)];
}


void AWaypoint::PostEditChangeProperty(FPropertyChangedEvent& e)
{
	if (e.Property && e.Property->GetFName() == GET_MEMBER_NAME_CHECKED(AWaypoint, Radius))
	{
		SphereComp->SetSphereRadius(Radius);
	}
	Super::PostEditChangeProperty(e);
}

float AWaypoint::GetRadius()
{
	return Radius;
}
