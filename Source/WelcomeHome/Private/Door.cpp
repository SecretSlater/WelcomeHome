// Fill out your copyright notice in the Description page of Project Settings.

#include "WelcomeHome.h"
#include "Door.h"


// Sets default values
ADoor::ADoor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	DummyRoot = CreateDefaultSubobject<USceneComponent>(TEXT("DummyRoot"));
	RootComponent = DoorMesh; // Dummy root added so that MainCharacter cannot grab this actor

	DoorMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("DoorMesh"));
	static ConstructorHelpers::FObjectFinder<UStaticMesh> CubeVisualAsset(TEXT("StaticMesh'/Game/Shapes/Shape_Cube.Shape_Cube'")); // Finds cube static mesh and sets it to CubeVisualAsset
	DoorMesh->SetStaticMesh(CubeVisualAsset.Object);
	DoorMesh->SetRelativeScale3D(FVector(0.2f, 0.8f, 2.0f)); // TODO Replace with actual static mesh of door/fix offset from root component
	DoorMesh->SetupAttachment(RootComponent);
}

// Called when the game starts or when spawned
void ADoor::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ADoor::Tick( float DeltaTime )
{
	Super::Tick( DeltaTime );

}

// Function triggered by successful Lock OnOverlap event (correct key to correct lock)
void ADoor::OpenDoor()
{
	// TODO Logic to open door
	UE_LOG(LogTemp, Warning, TEXT("OpenDoor function hit."));
}

