// All code generated by Aleix Rius for the Indie Spain Dev 2023. The code is delivered as is.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "BaseUserWidget.generated.h"

/**
 *
 */
UCLASS()
class SPAINGAMEJAM2023_API UBaseUserWidget : public UUserWidget
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintCallable)
	void OnActivate();
	UFUNCTION(BlueprintCallable)
	void OnDeactivate();

protected: 

	UFUNCTION(BlueprintImplementableEvent)
	void Activate();

	UFUNCTION(BlueprintImplementableEvent)
	void Deactivate();

};
