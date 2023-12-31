// All code generated by Aleix Rius for the Indie Spain Dev 2023. The code is delivered as is.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "GameTypes.generated.h"




UENUM(BlueprintType)
enum class EGameModeStage : uint8
{
	PREPARATIONS UMETA(DisplayName = "Preparations"),
	COMBAT UMETA(DisplayName = "Combat")
};


UENUM(BlueprintType)
enum class EGameStatus : uint8
{
	PLAYING UMETA(DisplayName = "Playing"),
	VICOTRY UMETA(DisplayName = "Victory"),
	DEFEAT UMETA(DisplayName = "Defeat")
};

UENUM(BlueprintType)
enum class ECombatStats : uint8
{
	HEALTH UMETA(DisplayName = "Health"),
	DAMAGE UMETA(DisplayName = "Damage"),
	ATTACK_SPPED UMETA(DisplayName = "Attack Speed"),
	DEFENSE UMETA(DisplayName = "Defense"),
	PIERCING_DAMAGE UMETA(DisplayName = "Piercing Damage"),
	TEAM UMETA(DisplayName = "Team")
};

UCLASS()
class SPAINGAMEJAM2023_API UGameTypes : public UObject
{
	GENERATED_BODY()
};
