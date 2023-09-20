// All code generated by Aleix Rius for the Indie Spain Dev 2023. The code is delivered as is.

#pragma once

#include "CoreMinimal.h"
#include "BaseManager.h"
#include "Interfaces/ICombatInterface.h"
#include "TurretsManager.generated.h"

/**
 *
 */
UCLASS()
class SPAINGAMEJAM2023_API UTurretsManager : public UBaseManager
{
	GENERATED_BODY()


public:
	UFUNCTION(BlueprintCallable)
	void AddTurret(class ABaseTurret* newTurret);


	UFUNCTION(BlueprintCallable)
	void RemoveTurret(class ABaseTurret* turret);

	UFUNCTION(BlueprintCallable)
	void RemoveAndDestroyTurret(class ABaseTurret* turret);

	UFUNCTION(BlueprintCallable)
	const TArray<class ABaseTurret*>& GetTurretsList()const { return turretsList; }


	void OnChangeGameStage(EGameModeStage newStage) override;


private: 

	void DestroyTurret(class ABaseTurret* turret);
protected:

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	TArray<class ABaseTurret*> turretsList;
};
