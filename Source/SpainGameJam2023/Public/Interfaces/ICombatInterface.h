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
	float health = 5.f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float damage = 3.f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float attackSpeed = 1.5f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float defense = 1.f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float piercingDamagePercent = 0.05f;

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

	UFUNCTION(BlueprintNativeEvent)
	void DealDamage(float ammount) const;

	UFUNCTION(BlueprintNativeEvent)
	void ReceiveDamage(float ammount);

	UFUNCTION(BlueprintNativeEvent)
	void GetCombatStats(FCombatStats& out) const;

	UFUNCTION(BlueprintNativeEvent)
	void SetCombatStats(const FCombatStats& stats);
};