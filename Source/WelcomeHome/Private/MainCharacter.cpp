// Fill out your copyright notice in the Description page of Project Settings.

#include "WelcomeHome.h"
#include "MainCharacter.h"

AMainCharacter::AMainCharacter()
{
	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	RightHandMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("RightHandMesh"));
	LeftHandMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("LeftHandMesh"));

	RightHandMesh->SetupAttachment(LeftMotionController);
	LeftHandMesh->SetupAttachment(RightMotionController);

	static ConstructorHelpers::FObjectFinder<UStaticMesh> CubeVisualAsset(TEXT("StaticMesh'/Game/Shapes/Shape_Cube.Shape_Cube'")); // Finds cube static mesh and sets it to CubeVisualAsset

	if (CubeVisualAsset.Succeeded())
	{
		RightHandMesh->SetStaticMesh(CubeVisualAsset.Object);
		RightHandMesh->SetWorldScale3D(FVector(0.2f, 0.2f, 0.2f));

		LeftHandMesh->SetStaticMesh(CubeVisualAsset.Object);
		LeftHandMesh->SetWorldScale3D(FVector(0.2f, 0.2f, 0.2f));
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("Cube asset not found."));
	}

}

void AMainCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}
