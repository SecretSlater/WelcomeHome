// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "SimpleChar/VRSimpleCharacter.h"
#include "MainCharacter.generated.h"

/**
 * 
 */
UCLASS()
class WELCOMEHOME_API AMainCharacter : public AVRSimpleCharacter
{
	GENERATED_BODY()

public:
	AMainCharacter();

	virtual void Tick(float DeltaTime) override;

	virtual void SetupPlayerInputComponent(class UInputComponent* InputComponent) override;
	
private:
	UStaticMeshComponent* RightHandMesh;
	UStaticMeshComponent* LeftHandMesh;

	// Input commands
	void MoveY(float AxisValue);
	void MoveX(float AxisValue);

	UPROPERTY(EditAnywhere)
	float MovementSpeed = 0.2f;
};
