// All code generated by Aleix Rius for the Indie Spain Dev 2023. The code is delivered as is.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "BuildingPawn.generated.h"

UCLASS()
class SPAINGAMEJAM2023_API ABuildingPawn : public APawn
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	ABuildingPawn();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UFUNCTION(BlueprintNativeEvent)
	void SpaceBarPressed();
	void SpaceBarPressed_Implementation();

	void PossessedBy(AController* NewController) override;
	void UnPossessed()override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	UFUNCTION(BlueprintCallable)
	void PickBuildingObject(TSubclassOf<class APlaceableBaseActor> object);


	UFUNCTION(BlueprintCallable)
	void PlaceCurrentActor();

protected: 
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category ="Building")
	TMap<TSubclassOf<class APlaceableBaseActor>, TSubclassOf<class ABaseBuildingActor>> buildingModels;

	UPROPERTY(VisibleAnywhere, Category ="Building")
	TSubclassOf<class APlaceableBaseActor> selectedActor;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category ="Building")
	class ABaseBuildingActor* currentObject;
};
