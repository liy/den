// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Guest.generated.h"

UCLASS()
class DEN_API AGuest : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AGuest();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	// Default behaviour for the guest, set in the blueprint
	UPROPERTY(EditAnywhere, Category = "AI")
	class UBehaviorTree* Behavior;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	UBehaviorTree* GetBehavior();
	
};
