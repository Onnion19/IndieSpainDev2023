// All code generated by Aleix Rius for the Indie Spain Dev 2023. The code is delivered as is.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Interfaces/ICombatInterface.h"
#include "PlaceableBaseActor.h"
#include "BaseTurret.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnReceiveDamageSignature, float, damage);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnActorRangeSignature, AActor*, actor);


UENUM(BlueprintType)
enum class ETurretMode : uint8 {
	IDLE UMETA(DisplayName = "Idle"),
	FIRING UMETA(Displayname = "Firing")
};

UCLASS()
class SPAINGAMEJAM2023_API ABaseTurret : public APlaceableBaseActor, public ICombatInterface
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	ABaseTurret();


private:

	UFUNCTION()
	void StartFiringMode();

	UFUNCTION()
	void StopFiringMode();
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	void BeginDestroy() override;

	UFUNCTION(BlueprintCallable, CallInEditor)
	void UpdateAttackRangeMesh(float arange);

	UFUNCTION()
	void OnActorEnterAttackRange(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);
	UFUNCTION(BlueprintImplementableEvent)
	void OnActorEnterAttackRangeBP(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	UFUNCTION()
	void OnActorLeavesAttackRange(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);
	UFUNCTION(BlueprintImplementableEvent)
	void OnActorLeavesAttackRangeBP(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);

	UFUNCTION(BlueprintImplementableEvent)
	void OnFireCommand();

	UFUNCTION()
	void OnFire();

	UFUNCTION(BlueprintImplementableEvent)
	void TickBP(float deltaTime);
public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;


	// ICombatInterface 
	void DealDamage_Implementation(float ammount) const override;
	void ReceiveDamage_Implementation(float ammount) override;
	void GetCombatStats_Implementation(FCombatStats& out) const override;
	void SetCombatStats_Implementation(const FCombatStats& stats) override;
	// ~ICombatInterface

	UFUNCTION(BlueprintCallable)
	void Fire(AActor* target);

	UFUNCTION(BlueprintCallable)
	void SwapToMode(ETurretMode newMode);

	UFUNCTION(BlueprintCallable)
	ETurretMode GetTurretMode()const;

	UFUNCTION(BlueprintCallable)
	void ActivateTurret();

	UFUNCTION(BlueprintCallable)
	void DeactivateTurret();

	UFUNCTION(BlueprintCallable, CallInEditor, Category = "Turret Stats")
	void ShowAttackRangeIndicator();

	UFUNCTION(BlueprintCallable, CallInEditor, Category = "Turret Stats")
	void HideAttackRangeIndicator();

protected:

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Combat Interface")
	FCombatStats combatStats;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Combat Interface")
	bool bIsActive = true;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Turret Stats")
	float attackRange = 100.f;

	UPROPERTY(EditAnywhere, Category = "Turret Visibility")
	class UStaticMeshComponent* turretRangeIndicator;

	UPROPERTY(VisibleAnywhere, Category = "Turret Visibility")
	class USphereComponent* turretRangeCollider;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Turret Visibility")
	TArray<AActor*> closestActors;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Turret Stats")
	ETurretMode turretMode;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Buidling")
	float rangeAreaOffset = 50.f;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	FRotator rangeIndicatorRotation;

	bool bIsShowingRangeIndicator = false;

	// Timers
	UPROPERTY()
	FTimerHandle firingTimer;

	// DELEGATES
	UPROPERTY(BlueprintAssignable)
	FOnReceiveDamageSignature onReceiveDamage;

	UPROPERTY(BlueprintAssignable)
	FOnActorRangeSignature onActorEntersRange;

	UPROPERTY(BlueprintAssignable)
	FOnActorRangeSignature onActorLeavesRange;
};
