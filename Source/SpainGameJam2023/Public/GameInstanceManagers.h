// All code generated by Aleix Rius for the Indie Spain Dev 2023. The code is delivered as is.

#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "Utils/GameTypes.h"
#include "GameInstanceManagers.generated.h"


DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnGameEndSignature);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnStageChangesignature, EGameModeStage, stage);
/**
 *
 */
UCLASS()
class SPAINGAMEJAM2023_API UGameInstanceManagers : public UGameInstance
{
	GENERATED_BODY()

private:
	void CreateEnergyManager();
	void CreateTurretsManager();

public:
	void Init() override;

	UFUNCTION(BlueprintCallable)
	class UEnergyManager* GetEnergyManager() const { return energyManager; }

	UFUNCTION(BlueprintCallable)
	class AHUDManager* GetHudManager() const;

	UFUNCTION(BlueprintCallable)
	class UTurretsManager* GetTurretsManager() const { return turretsManager; }


	UFUNCTION(BlueprintCallable)
	void SetGamePlayManager(class AGameplayManager* manager) { if (!gameplayManager) gameplayManager = manager; }

	UFUNCTION(BlueprintCallable)
	class AGameplayManager* GetGameplaymanager()const { return gameplayManager; }

	UFUNCTION(BlueprintCallable)
	void ChangeGameStage(EGameModeStage newStage);

	UFUNCTION(BlueprintCallable)
	EGameModeStage GetCurrentStage()const { return stage; }

	UFUNCTION(BlueprintCallable)
	void Defeat();

	UFUNCTION(BlueprintCallable)
	void Win();

protected:

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Managers")
	class UEnergyManager* energyManager;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Managers")
	class UTurretsManager* turretsManager;

	UPROPERTY(BlueprintReadonly, Visibleanywhere, Category = "Managers")
	class AGameplayManager* gameplayManager;

	UPROPERTY(BlueprintReadOnly)
	EGameModeStage stage;

public:
	UPROPERTY(BlueprintAssignable)
	FOnGameEndSignature OnGameOver;

	UPROPERTY(BlueprintAssignable)
	FOnGameEndSignature OnVictory;
	UPROPERTY(BlueprintAssignable)
	FOnStageChangesignature OnChangeGameStage;
};
