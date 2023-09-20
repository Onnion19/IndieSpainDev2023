// All code generated by Aleix Rius for the Indie Spain Dev 2023. The code is delivered as is.

#pragma once

#include "CoreMinimal.h"
#include "Interfaces/ICombatInterface.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "CombatUtilsLibrary.generated.h"

/**
 *
 */
UCLASS()
class SPAINGAMEJAM2023_API UCombatUtilsLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintCallable, Category = "Combat Utils")
	static void ResolveCombatStatsByActors(AActor* dealer, AActor* receiver);

	UFUNCTION(BlueprintCallable, Category = "Combat Utils")
	static void ResolveMultipleCombatStatsByActors(AActor* dealer, TArray<AActor*> receivers);

	UFUNCTION(BlueprintCallable)
	static FCombatStats Multiply(const FCombatStats& stats, float multiplier);

	UFUNCTION(BlueprintCallable)
	static FCombatStats Add(const FCombatStats& a, const FCombatStats& b);

	UFUNCTION(BlueprintCallable)
	static FCombatStats Withdraw(const FCombatStats& a, const FCombatStats& b);

private: 

	UFUNCTION()
	static float ResolveCombatStats(const FCombatStats& dealer, const FCombatStats& receiver);

};
