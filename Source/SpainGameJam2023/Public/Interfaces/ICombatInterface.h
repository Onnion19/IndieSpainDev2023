// Fill out your copyright notice in the Description page of Project Settings.

#pragma once
#include "ICombatInterface.generated.h"


USTRUCT(BlueprintType)
struct FCombatStats {
	GENERATED_BODY()

	UPROPERTY(EditAnywhere)
	float health;

	UPROPERTY(EditAnywhere)
	float damage;

	UPROPERTY(EditAnywhere)
	float attackSpeed;

	UPROPERTY(EditAnywhere)
	float defense;

	UPROPERTY(EditAnywhere)
	float piercingDamagePercent;
};


UINTERFACE(MinimalAPI, Blueprintable)
class UCombatInterface : public UInterface
{
	GENERATED_BODY()
};

class ICombatInterface
{
	GENERATED_BODY()

public:

	UFUNCTION()
	virtual void DealDamage(float ammount) const = 0;

	UFUNCTION()
	virtual void ReceiveDamage(float ammount) = 0;

	UFUNCTION()
	virtual FCombatStats GetCombatStats() const = 0;

	UFUNCTION()
	virtual void SetCombatStats(const FCombatStats& stats) = 0;
};