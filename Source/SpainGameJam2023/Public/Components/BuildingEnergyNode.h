// All code generated by Aleix Rius for the Indie Spain Dev 2023. The code is delivered as is.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "BuildingEnergyNode.generated.h"


UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class SPAINGAMEJAM2023_API UBuildingEnergyNode : public UActorComponent
{
	GENERATED_BODY()

public:

	inline const static FName ENERGY_TAG = { "Energy" };

	// Sets default values for this component's properties
	UBuildingEnergyNode();

	void BeginPlay() override;

	UFUNCTION(BlueprintCallable)
	void NewOutPipe(class ABaseEnergyPipe* pipe);

	UFUNCTION(BlueprintCallable)
	void NewInPipe(class ABaseEnergyPipe* pipe);

	UFUNCTION(BlueprintCallable)
	void RemovePipe(class ABaseEnergyPipe* pipe);

	UFUNCTION(BlueprintCallable)
	void GetOutPipes(TArray<class ABaseEnergyPipe*>& pipes)const;

	UFUNCTION(BlueprintCallable)
	class ABaseEnergyPipe* GetInPipe()const;

	UFUNCTION(BlueprintCallable)
	void SetEnergyIncome(float energyLevel);

	UFUNCTION(BlueprintCallable)
	float GetEnergyConsumption() const;

	UFUNCTION(BlueprintCallable)
	float GetNodeEnergy()const;

protected: 

	class ABaseEnergyStation* FindClosestStation();

	void ConnectToStation(class ABaseEnergyStation* station);

protected:

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	float energyConsumption;

	UPROPERTY(BlueprintReadOnly, VisibleAnywhere)
	float incomingEnergy;

	UPROPERTY(BlueprintReadOnly, VisibleAnywhere)
	TArray<class ABaseEnergyPipe*> outPipes;

	UPROPERTY(BlueprintReadOnly, VisibleAnywhere)
	class ABaseEnergyPipe* inPipe;

};
