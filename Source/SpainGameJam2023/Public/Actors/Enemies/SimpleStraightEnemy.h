// All code generated by Aleix Rius for the Indie Spain Dev 2023. The code is delivered as is.

#pragma once

#include "CoreMinimal.h"
#include "Actors/BaseEnemy.h"
#include "SimpleStraightEnemy.generated.h"

/**
 * 
 */
UCLASS()
class SPAINGAMEJAM2023_API ASimpleStraightEnemy : public ABaseEnemy
{
	GENERATED_BODY()
public: 

	UFUNCTION(BlueprintCallable)
	void InitMovementData(const FVector& direction, float speed);
	void Tick(float deltaTime) override;
protected: 

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	float speed = 10.f;

};
