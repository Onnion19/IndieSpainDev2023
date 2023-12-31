// All code generated by Aleix Rius for the Indie Spain Dev 2023. The code is delivered as is.


#include "Actors/BuildingPawn.h"
#include "Actors/BaseTurret.h"
#include "Actors/BaseBuildingActor.h"
#include "Actors/PlaceableBaseActor.h"
#include "GameInstanceManagers.h"
#include "Actors/GameplayManager.h"


// Sets default values
ABuildingPawn::ABuildingPawn()
{
	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void ABuildingPawn::BeginPlay()
{
	Super::BeginPlay();
	if (auto gInstance = Cast<UGameInstanceManagers>(GetGameInstance()))
	{
		gInstance->OnChangeGameStage.AddDynamic(this, &ABuildingPawn::OnGameStageChange);
	}
}

// Called every frame
void ABuildingPawn::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	if (!currentObject)return;

	auto pController = Cast<APlayerController>(GetController());
	if (!pController)return;

	FVector worldlLocation{};
	FVector worldDirection{};
	// Try to find mouse position in the 3d world.
	if (pController->DeprojectMousePositionToWorld(worldlLocation, worldDirection))
	{
		if (isBuilding)	PerformRayTraceBuildingActor(worldlLocation, worldDirection);
		//else PerformRayTraceCombatActor(worldlLocation, worldDirection);
	}
}

// Called to bind functionality to input
void ABuildingPawn::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
	PlayerInputComponent->BindKey(EKeys::SpaceBar, EInputEvent::IE_Released, this, &ABuildingPawn::SpaceBarPressed);
}


void ABuildingPawn::SpaceBarPressed_Implementation()
{
	PlaceCurrentActor();
}

void ABuildingPawn::OnGameStageChange(EGameModeStage stage)
{
	SetIsBuidling(false);
}




void ABuildingPawn::PickBuildingObject(TSubclassOf<APlaceableBaseActor> object) {

	auto candidate = buildingModels.Find(object);
	if (!candidate)
	{
		UE_LOG(LogTemp, Error, TEXT("Could not find a matching building actor for: %s"), *(object->StaticClass()->GetName()));
		return;
	}

	selectedActorClass = object;

	if (currentObject) {
		currentObject->Destroy();
	}

	currentObject = Cast<ABaseBuildingActor>(GetWorld()->SpawnActor(*candidate));

}



void ABuildingPawn::PlaceCurrentActor() {
	if (!isBuilding)return;
	if (!currentObject)return;
	if (!currentObject->CanBePlaced())return;

	FActorSpawnParameters params;
	params.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AdjustIfPossibleButAlwaysSpawn;

	auto newTurret = GetWorld()->SpawnActor<APlaceableBaseActor>(selectedActorClass, currentObject->GetActorTransform(), params);
	ensureMsgf(newTurret, TEXT("Trying to spawn an invaldi turret"));

	auto gInstance = Cast<UGameInstanceManagers>(GetWorld()->GetGameInstance());
	if (!gInstance)
	{
		UE_LOG(LogTemp, Error, TEXT("Could not fetch game instance with class UGameInstanceManagers"));
		return;
	}

	auto gampleyManager = gInstance->GetGameplaymanager();
	if (!gampleyManager) return;
	gampleyManager->AddGold(-currentObject->GetCost());

}

void ABuildingPawn::SetIsBuidling(bool flag)
{
	if (isBuilding == flag) return;
	isBuilding = flag;

	if (!isBuilding && currentObject)
		currentObject->Destroy();


	if (isBuilding)	onStartBuildingMode.Broadcast();
	else onStopBuildingMode.Broadcast();
}

bool ABuildingPawn::GetIsBuidling() const
{
	return isBuilding;
}

void ABuildingPawn::AddBuildingObject(TSubclassOf<class APlaceableBaseActor> object, TSubclassOf<class ABaseBuildingActor> placeholder)
{
	auto t = buildingModels.Find(object);
	if (t) return;
	buildingModels.Add(object, placeholder);
	onChangedList.Broadcast();
}

void ABuildingPawn::RemoveBuildingObject(TSubclassOf<class APlaceableBaseActor> object)
{
	if (buildingModels.Remove(object))
	{
		onChangedList.Broadcast();
	}
}

void ABuildingPawn::SelectActor(AActor* actor)
{
	selectedActor = actor;
	onHoverCombatActor.Broadcast(selectedActor);
}

void ABuildingPawn::PerformRayTraceBuildingActor(const FVector& location, const FVector& direction)
{
	FHitResult hit{};
	FCollisionQueryParams params;
	params.AddIgnoredActor(this);
	const FVector end = location + (direction * 10000000);
	// See where the mouse is pointint to place the new turret
	if (GetWorld()->LineTraceSingleByChannel(hit, location, end, ECollisionChannel::ECC_GameTraceChannel4, params))
	{
		if (!hit.Normal.Equals(FVector::UpVector, 0.001f)) return;
		const auto& hitLocation = hit.ImpactPoint;
		currentObject->SetActorLocation(hitLocation);
		DrawDebugLine(GetWorld(), location, hit.Location, FColor::Green, false, 0.3f, 0u, 0.2f);
	}
	else
	{
		DrawDebugLine(GetWorld(), location, end, FColor::Red, false, 10.f, 0u, 0.5f);
	}
}

void ABuildingPawn::PerformRayTraceCombatActor(const FVector& location, const FVector& direction)
{
	FHitResult hit{};
	FCollisionQueryParams params;
	params.AddIgnoredActor(this);
	const FVector end = location + (direction * 5000);
	// See where the mouse is pointint to place the new turret
	if (GetWorld()->LineTraceSingleByChannel(hit, location, end, ECollisionChannel::ECC_Visibility, params))
	{
		if (hit.GetActor()->Implements<UCombatInterface>()) {
			DrawDebugLine(GetWorld(), location, hit.Location, FColor::Blue, false, 0.3f, 0u, 0.2f);
			onHoverCombatActor.Broadcast(hit.GetActor());
		}
		else {
			onStopHoverCombatActor.Broadcast();
		}

	}
	else
	{
		DrawDebugLine(GetWorld(), location, end, FColor::Yellow, false, 10.f, 0u, 0.5f);

	}
}
