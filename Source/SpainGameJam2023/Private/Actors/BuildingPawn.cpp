// All code generated by Aleix Rius for the Indie Spain Dev 2023. The code is delivered as is.


#include "Actors/BuildingPawn.h"
#include "Actors/BaseTurret.h"
#include "Actors/BaseBuildingActor.h"
#include "Actors/PlaceableBaseActor.h"
#include "GameInstanceManagers.h"
#include "Actors/GameplayManager.h"
#include "TurretsManager.h"

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
		FHitResult hit{};
		FCollisionQueryParams params;
		params.AddIgnoredActor(this);
		// See where the mouse is pointint to place the new turret
		if (GetWorld()->LineTraceSingleByChannel(hit, worldlLocation, worldlLocation + (worldDirection * 10000), ECollisionChannel::ECC_GameTraceChannel4, params))
		{
			const auto& hitLocation = hit.Location;
			currentObject->SetActorLocation(hitLocation);
			DrawDebugLine(GetWorld(), worldlLocation, hit.Location, FColor::Green, false, 0.3f, 0u, 0.2f);
		}
		else
		{
			DrawDebugLine(GetWorld(), worldlLocation, worldlLocation + (worldDirection * 5000), FColor::Red, false, 1.f, 0u, 0.5f);
		}


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


void ABuildingPawn::PossessedBy(AController* NewController)
{
	Super::PossessedBy(NewController);
	APlayerController* playerController = Cast<APlayerController>(NewController);
	if (!playerController) return;

	playerController->bShowMouseCursor = true;
}

void ABuildingPawn::UnPossessed()
{

}



void ABuildingPawn::PickBuildingObject(TSubclassOf<APlaceableBaseActor> object) {

	auto candidate = buildingModels.Find(object);
	if (!candidate)
	{
		UE_LOG(LogTemp, Error, TEXT("Could not find a matching building actor for: %s"), *(object->StaticClass()->GetName()));
		return;
	}

	selectedActor = object;

	if (currentObject) {
		currentObject->Destroy();
	}

	currentObject = Cast<ABaseBuildingActor>(GetWorld()->SpawnActor(*candidate));

}



void ABuildingPawn::PlaceCurrentActor() {
	if (!currentObject)return;
	if (!currentObject->CanBePlaced())return;

	FActorSpawnParameters params;
	params.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AdjustIfPossibleButAlwaysSpawn;

	auto newTurret = GetWorld()->SpawnActor<ABaseTurret>(selectedActor, currentObject->GetActorTransform(), params);
	ensureMsgf(newTurret, TEXT("Trying to spawn an invaldi turret"));

	auto gInstance = Cast<UGameInstanceManagers>(GetWorld()->GetGameInstance());
	if (!gInstance)
	{
		UE_LOG(LogTemp, Error, TEXT("Could not fetch game instance with class UGameInstanceManagers"));
		return;
	}

	auto turretsManager = gInstance->GetTurretsManager();
	if (!turretsManager)
	{
		UE_LOG(LogTemp, Error, TEXT("Could not fetch turrets manager from game instance"));
		return;
	}

	// [TODO] Probably this turrets manager can be removed
	turretsManager->AddTurret(newTurret);
	auto gampleyManager = gInstance->GetGameplaymanager();
	if (!gampleyManager) return;
	gampleyManager->PlayerStructureCreated(newTurret);

}