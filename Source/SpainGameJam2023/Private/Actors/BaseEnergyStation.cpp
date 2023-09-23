// All code generated by Aleix Rius for the Indie Spain Dev 2023. The code is delivered as is.


#include "Actors/BaseEnergyStation.h"
#include "Components/EnergyPipeBuilder.h"
#include "Components/BuildingEnergyNode.h"
#include "Kismet/GameplayStatics.h"

// Sets default values
ABaseEnergyStation::ABaseEnergyStation()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;
	energyNode = CreateDefaultSubobject<UBuildingEnergyNode>("Energy Node");

	energyBuilder = CreateDefaultSubobject<UEnergyPipeBuilder>("Energy builder");

}

// Called when the game starts or when spawned
void ABaseEnergyStation::BeginPlay()
{
	Super::BeginPlay();
	energyNode->SetEnergyIncome(energy);

	TArray<AActor*> FoundActors;
	UGameplayStatics::GetAllActorsWithTag(GetWorld(), UBuildingEnergyNode::ENERGY_TAG, FoundActors);
	const float threshold = range * range;
	for (auto& actor : FoundActors)
	{
		if (actor == this) continue;
		auto node = actor->GetComponentByClass<UBuildingEnergyNode>();
		if (!node)continue;

		auto distance = static_cast<float>(FVector::DistSquared(GetActorLocation(), actor->GetActorLocation()));
		if (distance < threshold)
		{
			connectedComponents.Add(node);
		}
	}

	RebuildPipeGraph();
}

void ABaseEnergyStation::RebuildPipeGraph()
{
	energyBuilder->RebuildPipeGraphFromNode(energyNode, connectedComponents);
}

void ABaseEnergyStation::Connect(UBuildingEnergyNode* node)
{
	connectedComponents.AddUnique(node);
}

void ABaseEnergyStation::Disconnect(UBuildingEnergyNode* node)
{
	connectedComponents.Remove(node);
}

