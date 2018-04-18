// Fill out your copyright notice in the Description page of Project Settings.

#include "Guest.h"


// Sets default values
AGuest::AGuest()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	Wallet = 100.0f;
}

// Called when the game starts or when spawned
void AGuest::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AGuest::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void AGuest::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

UBehaviorTree * AGuest::GetBehavior()
{
	return Behavior;
}

float AGuest::GetWallet()
{
	return Wallet;
}

bool AGuest::CanPay(float Cost)
{
	return (Wallet - Cost) >= 0;
}

bool AGuest::Pay(float Cost)
{
	float remain = Wallet - Cost;
	if (remain >= 0) {
		Wallet = remain;
		WalletAmountChanged();
		return true;
	}
	return false;
}

