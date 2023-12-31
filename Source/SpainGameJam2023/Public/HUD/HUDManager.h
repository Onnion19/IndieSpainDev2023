// All code generated by Aleix Rius for the Indie Spain Dev 2023. The code is delivered as is.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/HUD.h"
#include "AllAgainstTheStarsGameMde.h"
#include <functional>
#include "HUDManager.generated.h"


USTRUCT(BlueprintType)
struct FStageWidgetsArray {
	GENERATED_BODY()

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	TArray<class UStageWidgets*> widgets;
};

/**
 *
 */
UCLASS()
class SPAINGAMEJAM2023_API AHUDManager : public AHUD
{
	GENERATED_BODY()

public:


	void ChangeStage(EGameModeStage stage);

	UFUNCTION(BlueprintCallable)
	void RegisterStageWidget(EGameModeStage stage, class UStageWidgets* widget);

	UFUNCTION(BlueprintCallable)
	void UnRegisterStageWidget(EGameModeStage stage, class UStageWidgets* widget);


	UFUNCTION(BlueprintCallable)
	void RegisterTutorialWidget(class UBaseUserWidget* widget);

	UFUNCTION(BlueprintCallable)
	class UBaseUserWidget* GetTutorialWidget()const;

	UFUNCTION(BlueprintCallable)
	void Show();

	UFUNCTION(BlueprintCallable)
	void Hide();
private: 

	void ActivateStageWidgets(EGameModeStage stage);
	void DeactivateStageWidgets(EGameModeStage stage);


protected:

	void BeginPlay()override;

	UPROPERTY(BlueprintReadOnly, VisibleAnywhere)
	TMap<EGameModeStage, FStageWidgetsArray> stageWidgets;

	UPROPERTY(BlueprintReadOnly, EditAnywhere)
	TSubclassOf<class UBaseUserWidget> rootClass;

	UPROPERTY(BlueprintReadOnly, EditAnywhere)
	class UBaseUserWidget* tutorialWidget;

	UPROPERTY(BlueprintReadOnly, VisibleAnywhere)
	class UBaseUserWidget* root;

	EGameModeStage currentStage;

};
