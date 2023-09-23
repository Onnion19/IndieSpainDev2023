// All code generated by Aleix Rius for the Indie Spain Dev 2023. The code is delivered as is.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Utils/GameTypes.h"
#include "GameplayManager.generated.h"


DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnWaveEndSignature);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnPlayerStructureDestroyedSignature, AActor*, structure);


UCLASS()
class SPAINGAMEJAM2023_API AGameplayManager : public AActor
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	AGameplayManager();

protected:

	void PostInitializeComponents() override;

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UFUNCTION(BlueprintImplementableEvent)
	void OnWaveStartBP();

	UFUNCTION(BlueprintImplementableEvent)
	void OnWaveEndBP();

	UFUNCTION(BlueprintImplementableEvent)
	void OnGameModeChangeBP(EGameModeStage stage);

public:

	UFUNCTION(BlueprintCallable)
	EGameStatus GetGamestatus();

	void OnChangeGameStage(EGameModeStage stage);

	UFUNCTION(BlueprintCallable)
	void SpawnWave(int32 wave);

	UFUNCTION(BlueprintCallable)
	int32 GetNumWaves()const;

	UFUNCTION(BlueprintCallable)
	UEnemyDataAsset* GetCurrentWave(int32& waveIndex)const;

	UFUNCTION(BlueprintCallable)
	void StopWave();

	UFUNCTION(BlueprintCallable)
	void PlayerStructureCreated(AActor* structure);

	UFUNCTION(BlueprintCallable)
	void PlayerStructureDestroyed(AActor* structure);

	UFUNCTION(BlueprintCallable)
	void GetPlayerStructures(TArray<AActor*>& structures)const;

	UFUNCTION(BlueprintCallable)
	TArray<class ABaseBeaconActor*> GetPlayerBeacons()const;

	template<typename T>
	TArray<T*> GetPlayerStructuresByType()const
	{
		TArray<T*> actors{};
		for (auto& actor : playerStructures)
		{
			if (auto type = Cast<T>(actor))
			{
				actors.Add(type);
			}
		}
		return actors;
	}

	UFUNCTION(BlueprintCallable)
	void OnNewEnemySpawn(class ABaseEnemy* enemy);

	UFUNCTION(BlueprintCallable)
	void EnemyDestroyed(class ABaseEnemy* enemy);

private:

	void Defeat();

	void EnablePlayerStructures();

	void DisablePlayerStructures();

	void SearchSpawner();

protected:


	UPROPERTY(BlueprintReadOnly, VisibleAnywhere)
	EGameStatus gameStatus;

	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "Player")
	TArray<AActor*> playerStructures;

	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "Wave")
	class AEnemySpawner* spawner;

	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "Wave")
	TArray<class UEnemyDataAsset*> waves;

	UPROPERTY(BlueprintReadOnly, VisibleAnywhere, Category = "Wave")
	int32 currentWave = 0;

	UPROPERTY(BlueprintReadOnly, VisibleAnywhere, Category = "Wave")
	TArray<class ABaseEnemy*> spawnedEnemies;

public:
	UPROPERTY(BlueprintAssignable)
	FOnWaveEndSignature OnWaveEnd;

	UPROPERTY(BlueprintAssignable)
	FOnPlayerStructureDestroyedSignature OnPlayerStrucureDestroyed;
};
