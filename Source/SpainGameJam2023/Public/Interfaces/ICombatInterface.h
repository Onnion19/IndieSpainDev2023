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
	float damage = 5.f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float attackSpeed = 1.5f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float defense = 1.f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float piercingDamagePercent = 0.4f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float requiredEnergy = 1.f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	ECombatTeam team = ECombatTeam::ENEMY;
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

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
	void DealDamage(float ammount) const;

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
	float ReceiveDamage(float ammount);

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
	void GetCombatStats(FCombatStats& out) const;

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
	void SetCombatStats(const FCombatStats& stats);
};