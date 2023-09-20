// All code generated by Aleix Rius for the Indie Spain Dev 2023. The code is delivered as is.


#include "HUD/HUDManager.h"
#include "HUD/StageWidgets.h"
void AHUDManager::ChangeStage(EGameModeStage stage)
{
	if (currentActiveStageWidget)
	{
		currentActiveStageWidget->DeActivate();
	}

	auto newWidget = stageWidgets.Find(stage);

	if (newWidget && *newWidget)
	{
		(*newWidget)->Activate();
	}
}