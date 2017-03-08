// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/Actor.h"
#include "Lock.generated.h"

UENUM(BlueprintType)
enum class EColorEnum : uint8
{
	CE_Blue		UMETA(DisplayName = "Blue"),
	CE_White	UMETA(DisplayName = "White"),
	CE_Red		UMETA(DisplayName = "Red")
};

class ADoor;

UCLASS()
class WELCOMEHOME_API ALock : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ALock();

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	
	// Called every frame
	virtual void Tick( float DeltaSeconds ) override;

private:
	UFUNCTION()
	void OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	UFUNCTION(BlueprintCallable, Category = "Setup")
	void SetADoor();

	UFUNCTION()
	bool SetLockColorStrings();

	UPROPERTY(EditAnywhere)
	USceneComponent* RootScene;

	UPROPERTY(EditAnywhere)
	UStaticMeshComponent* LockMesh;

	UPROPERTY(EditAnywhere)
	UBoxComponent* CollisionBox;

	UPROPERTY(EditAnywhere, Category = "Setup")
	TEnumAsByte<EColorEnum> LockColor; // Defaults to blue

	ADoor* DoorReference;

	FString DoorName; // Name of door to get reference too. Ex: A blue lock sets DoorName to "BlueDoor".

	FString KeyName; // Name of key to open lock. Ex: A blue lock requires a "BlueKey" to open.
};
