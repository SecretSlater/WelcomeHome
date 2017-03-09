// Fill out your copyright notice in the Description page of Project Settings.

#include "WelcomeHome.h"
#include "Door.h"
#include "EngineUtils.h"
#include "Lock.h"

// Sets default values
ALock::ALock()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	RootScene = CreateDefaultSubobject<USceneComponent>(TEXT("RootScene")); // Dummy root scene
	RootComponent = RootScene;

	LockMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("LockMesh"));
	static ConstructorHelpers::FObjectFinder<UStaticMesh> CubeVisualAsset(TEXT("StaticMesh'/Game/Shapes/Shape_Cube.Shape_Cube'")); // Finds cube static mesh and sets it to CubeVisualAsset
	LockMesh->SetStaticMesh(CubeVisualAsset.Object);
	LockMesh->SetRelativeScale3D(FVector(0.2f, 0.2f, 0.2f));
	LockMesh->SetupAttachment(RootScene);

	CollisionBox = CreateDefaultSubobject<UBoxComponent>(TEXT("CollisionBox"));
	CollisionBox->SetBoxExtent(FVector(90.0f, 60.0f, 60.0f)); // Sets size of box around the LockMesh
	CollisionBox->SetRelativeLocation(FVector(40.0f, 0.0f, 60.0f));
	CollisionBox->SetupAttachment(LockMesh);

	CollisionBox->OnComponentBeginOverlap.AddDynamic(this, &ALock::OnOverlapBegin); // Sets function to call when component is overlapped with CollisionBox
}

// Called when the game starts or when spawned
void ALock::BeginPlay()
{
	Super::BeginPlay();
	
	SetLockColorStrings();
	SetADoor();
}

// Called every frame
void ALock::Tick( float DeltaTime )
{
	Super::Tick( DeltaTime );

}

// Sets strings required in SetADoor() and OnOverlapBegin() 
bool ALock::SetLockColorStrings()
{
	if (LockColor == EColorEnum::CE_Blue)
	{
		DoorName = FString(TEXT("BlueDoor"));
		KeyName = FString(TEXT("BlueKey"));
		return true;
	}
	else if (LockColor == EColorEnum::CE_White)
	{
		DoorName = FString(TEXT("WhiteDoor"));
		KeyName = FString(TEXT("WhiteKey"));
		return true;
	}
	else if (LockColor == EColorEnum::CE_Red)
	{
		DoorName = FString(TEXT("RedDoor"));
		KeyName = FString(TEXT("RedKey"));
		return true;
	}
	else
	{
		return false;
	}
}

// Iterates through all spawned actors in level and looks for Door with matching Door name
// There's probably a better way to get the door reference, but this is what I have that works for now
void ALock::SetADoor()
{
	for (TActorIterator<ADoor> ActorItr(GetWorld()); ActorItr; ++ActorItr)
	{
		if (ActorItr->GetName().Contains(DoorName)) // Should probably change this from checking the name of the door to checking for a valid enum in Door
		{
			DoorReference = *ActorItr;
		}
	}
}

// Checks for actor overlapping the trigger box. Overlapping actor is stored in OtherActor. If the OtherActor is a valid key (ex: blue key on blue lock) it will
// delete the lock and open its corresponding door (unlocking blue lock opens blue door)
void ALock::OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (OtherActor->GetName().Contains(KeyName))
	{
		OtherActor->Destroy();
		DoorReference->OpenDoor();
		// TODO Call function to animate lock being unlocked by key
	}
}

