// All code generated by Aleix Rius for the Indie Spain Dev 2023. The code is delivered as is.


#include "Actors/BaseTurret.h"
#include "Components/StaticMeshComponent.h"
#include "Components/SphereComponent.h"
#include "Components/BoxComponent.h"
#include "Utils/CombatUtilsLibrary.h"
#include "GameInstanceManagers.h"
#include "TurretsManager.h"

// Sets default values
ABaseTurret::ABaseTurret()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	RootComponent = CreateDefaultSubobject<USceneComponent>("Root");
	// Turret Range
	turretRangeCollider = CreateDefaultSubobject<USphereComponent>("AtttackRangeCollider");
	turretRangeCollider->AttachToComponent(RootComponent, FAttachmentTransformRules{ EAttachmentRule::KeepRelative, false });
	turretRangeCollider->SetCollisionProfileName("TurretRangeIndicator");
	turretRangeCollider->SetCollisionObjectType(ECollisionChannel::ECC_GameTraceChannel1);

	turretRangeCollider->OnComponentBeginOverlap.AddDynamic(this, &ABaseTurret::OnActorEnterAttackRange);
	turretRangeCollider->OnComponentEndOverlap.AddDynamic(this, &ABaseTurret::OnActorLeavesAttackRange);

	// Turret Indicator
	turretRangeIndicator = CreateDefaultSubobject<UStaticMeshComponent>("AttackRangeVisible");
	turretRangeIndicator->AttachToComponent(turretRangeCollider, FAttachmentTransformRules{ EAttachmentRule::KeepRelative, false });
	turretRangeIndicator->SetCollisionEnabled(ECollisionEnabled::NoCollision);

	// Turret Bulding collider
	buildingCollider = CreateDefaultSubobject<UBoxComponent>("BuldingCollider");
	buildingCollider->AttachToComponent(RootComponent, FAttachmentTransformRules{ EAttachmentRule::KeepRelative, false });
	buildingCollider->SetCollisionProfileName({ "ConstructionBuilding" });



}

// Called when the game starts or when spawned
void ABaseTurret::BeginPlay()
{
	// Initialize variables
	Super::BeginPlay();
	SwapToMode(ETurretMode::IDLE);
	ActivateTurret();

}


void ABaseTurret::BeginDestroy() {
	Super::BeginDestroy();
}

// Called every frame
void ABaseTurret::Tick(float DeltaTime)
{
	ensureMsgf(bIsActive, TEXT("Turret tick called while turret is deactivated"));
	Super::Tick(DeltaTime);
}


// ICombatInterface 

void ABaseTurret::DealDamage_Implementation(float ammount) const {

}

void ABaseTurret::ReceiveDamage_Implementation(float ammount) {
	onReceiveDamage.Broadcast(ammount);
}

void ABaseTurret::GetCombatStats_Implementation(FCombatStats& out) const {
	out = combatStats;
}

void ABaseTurret::SetCombatStats_Implementation(const FCombatStats& stats) {
	combatStats = stats;
}
// ~ICombatInterface 


void ABaseTurret::OnFire()
{
	if (closestActors.IsEmpty())
	{
		// nothing to do
		return;
	}

	OnFireCommand();
}

void ABaseTurret::Fire(AActor* target)
{
	if (target == nullptr) return;

	UCombatUtilsLibrary::ResolveCombatStatsByActors(this, target);
}

void ABaseTurret::SwapToMode(ETurretMode newMode)
{

	StopFiringMode();
	turretMode = newMode;
	if (turretMode == ETurretMode::FIRING)
	{
		StartFiringMode();
		if (bIsActive)
			SetActorTickEnabled(true);
	}
	else
	{
		// only tick when requires to fire
		SetActorTickEnabled(false);
	}
}


void ABaseTurret::StartFiringMode() {
	ensureMsgf(combatStats.attackSpeed > 0.1f, TEXT("Can't start turret firing sequence: Fire rate to high: %d"), combatStats.attackSpeed);
	GetWorldTimerManager().SetTimer(firingTimer, this, &ABaseTurret::OnFire, combatStats.attackSpeed, true);
}


void ABaseTurret::StopFiringMode() {
	auto& timerManager = GetWorldTimerManager();
	if (timerManager.IsTimerActive(firingTimer))
		timerManager.ClearTimer(firingTimer);
}

ETurretMode ABaseTurret::GetTurretMode()const
{
	return turretMode;
}

void ABaseTurret::UpdateAttackRangeMesh(float arange) {

	const auto radius = static_cast<float>(turretRangeIndicator->GetStaticMesh()->GetBounds().SphereRadius);
	turretRangeIndicator->SetWorldScale3D(FVector{ arange, arange, arange } / radius);
	turretRangeCollider->SetSphereRadius(arange / 2);
	turretRangeCollider->SetRelativeLocation(FVector{ 0,0, (arange / 2) + rangeAreaOffset});

}

void ABaseTurret::OnActorEnterAttackRange(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (OtherActor->Implements<UCombatInterface>())
	{
		closestActors.Add(OtherActor);
		OnActorEnterAttackRangeBP(OverlappedComponent, OtherActor, OtherComp, OtherBodyIndex, bFromSweep, SweepResult);
		onActorEntersRange.Broadcast(OtherActor);
	}
}

void ABaseTurret::OnActorLeavesAttackRange(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	if (OtherActor->Implements<UCombatInterface>())
	{
		checkf(closestActors.Find(OtherActor) != INDEX_NONE, TEXT("A Combat interface actor is leaving the attack range but it wasn't registered on enter"));
		closestActors.Remove(OtherActor);
		OnActorLeavesAttackRangeBP(OverlappedComponent, OtherActor, OtherComp, OtherBodyIndex);
		onActorLeavesRange.Broadcast(OtherActor);
	}
}

void ABaseTurret::ActivateTurret() {
	bIsActive = true;
}

void ABaseTurret::DeactivateTurret() {
	bIsActive = false;
}

void ABaseTurret::ShowAttackRangeIndicator() {
	turretRangeIndicator->SetVisibility(true, true);
}
void ABaseTurret::HideAttackRangeIndicator() {
	turretRangeIndicator->SetVisibility(false, true);
}
