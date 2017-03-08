// Fill out your copyright notice in the Description page of Project Settings.

#include "WelcomeHome.h"
#include "DoorKey.h"


// Sets default values
ADoorKey::ADoorKey()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	KeyMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("KeyMesh"));
	static ConstructorHelpers::FObjectFinder<UStaticMesh> DoorKeyAsset(TEXT("StaticMesh'/Game/StaticMesh/Key'")); // Finds cube static mesh and sets it to DoorKeyAsset
	KeyMesh->SetStaticMesh(DoorKeyAsset.Object);

	RootComponent = KeyMesh; // Mesh MUST be root component for the MainCharacter to pick up
}

// Called when the game starts or when spawned
void ADoorKey::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ADoorKey::Tick( float DeltaTime )
{
	Super::Tick( DeltaTime );

}

