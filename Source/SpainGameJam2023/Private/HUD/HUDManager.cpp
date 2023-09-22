// All code generated by Aleix Rius for the Indie Spain Dev 2023. The code is delivered as is.


#include "HUD/HUDManager.h"
#include "HUD/StageWidgets.h"
#include "HUD/BaseUserWidget.h"
void AHUDManager::ActorSelected(AActor* actor)
{
	OnActorSelected.Broadcast(actor);
}

void AHUDManager::ChangeStage(EGameModeStage stage)
{
	if (stage == currentStage)return;

	DeactivateStageWidgets(currentStage);
	currentStage = stage;
	ActivateStageWidgets(stage);
}

void AHUDManager::RegisterStageWidget(EGameModeStage stage, UStageWidgets* widget)
{
	auto& wrapper = stageWidgets.FindOrAdd(stage);
	wrapper.widgets.AddUnique(widget);

}

void AHUDManager::UnRegisterStageWidget(EGameModeStage stage, UStageWidgets* widget)
{
	auto wrapper = stageWidgets.Find(stage);
	if (wrapper) {
		wrapper->widgets.Remove(widget);
	}
}

void AHUDManager::ActivateStageWidgets(EGameModeStage stage)
{
	auto widgetsWrapper = stageWidgets.Find(stage);
	if (widgetsWrapper)
	{
		auto& widgets = widgetsWrapper->widgets;
		std::for_each(widgets.begin(), widgets.end(), [](UStageWidgets* w) {w->Activate(); });
	}
}

void AHUDManager::DeactivateStageWidgets(EGameModeStage stage)
{
	auto widgetsWrapper = stageWidgets.Find(stage);
	if (widgetsWrapper)
	{
		auto& widgets = widgetsWrapper->widgets;
		std::for_each(widgets.begin(), widgets.end(), [](UStageWidgets* w) {w->DeActivate(); });
	}
}

void AHUDManager::BeginPlay()
{
	Super::BeginPlay();

	if (!rootClass) {
		UE_LOG(LogTemp, Error, TEXT("Plese specify a valid class for the root base widget"), );
		return;
	}

	root = CreateWidget<UBaseUserWidget>(GetWorld(), rootClass, FName{ "Root base widget" });

	if (!root)
	{
		UE_LOG(LogTemp, Error, TEXT("Could not create default base widget of class %s"), *(rootClass->GetName()));
		return;
	}

	root->AddToViewport();
	root->OnActivate();
}
