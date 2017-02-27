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
	
private:
	UStaticMeshComponent* RightHandMesh;
	UStaticMeshComponent* LeftHandMesh;
};
