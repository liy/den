// Fill out your copyright notice in the Description page of Project Settings.

#include "DenGameState.h"

void ADenGameState::PayIn(float Amount)
{
	TotalMoney += Amount;
}

bool ADenGameState::CanPayOut(float Amount)
{
	return (TotalMoney - Amount) >= 0.0f;
}

bool ADenGameState::PayOut(float Amount)
{
	float remain = TotalMoney - Amount;
	if (remain >= 0) {
		TotalMoney = remain;
		return true;
	}
	return false;
}