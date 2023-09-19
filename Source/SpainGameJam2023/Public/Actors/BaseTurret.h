// All code generated by Aleix Rius for the Indie Spain Dev 2023. The code is delivered as is.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Interfaces/ICombatInterface.h"
#include "BaseTurret.generated.h"

UCLASS()
class SPAINGAMEJAM2023_API ABaseTurret : public AActor, public ICombatInterface
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	ABaseTurret();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UFUNCTION(BlueprintCallable, BlueprintImplementableEvent, Category = "Combat Interface")
	void DealDamage(float ammount) const override;

	UFUNCTION(BlueprintCallable, BlueprintImplementableEvent, Category = "Combat Interface")
	void ReceiveDamage(float ammount) override;

	UFUNCTION(BlueprintCallable, BlueprintImplementableEvent, Category = "Combat Interface")
	FCombatStats GetCombatStats() const override;

	UFUNCTION(BlueprintCallable, BlueprintImplementableEvent, Category = "Combat Interface")
	void SetCombatStats(const FCombatStats& stats) override;


protected:

	UPROPERTY(EditAnywhere, Category = "Combat Interface")
	FCombatStats combatStats;

};
