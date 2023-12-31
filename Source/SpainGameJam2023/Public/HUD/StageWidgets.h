// All code generated by Aleix Rius for the Indie Spain Dev 2023. The code is delivered as is.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "StageWidgets.generated.h"

/**
 *
 */
UCLASS()
class SPAINGAMEJAM2023_API UStageWidgets : public UUserWidget
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintCallable)
	void Activate();

	UFUNCTION(BlueprintCallable)
	void DeActivate();

protected:
	UFUNCTION(BlueprintImplementableEvent)
	void ActivateBP();

	UFUNCTION(BlueprintImplementableEvent)
	void DeActivateBP();
protected:

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	TArray<class UBaseUserWidget*> widgets;
};
