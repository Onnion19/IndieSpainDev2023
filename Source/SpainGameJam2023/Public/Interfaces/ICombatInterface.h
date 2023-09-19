// Fill out your copyright notice in the Description page of Project Settings.

#pragma once
#include "ICombatInterface.generated.h"

UENUM(BlueprintType)
enum class ECombatTeam : uint8
{
	NEUTRAL UMETA(DisplayName = "Neutral"),
	FRIENDLY UMETA(DisplayName = "Friendly"), 
	ENEMY UMETA(DisplayName = "Enemy")
};

USTRUCT(BlueprintType)
struct FCombatStats {
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float health;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float damage;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float attackSpeed;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float defense;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float piercingDamagePercent;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	ECombatTeam team;
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