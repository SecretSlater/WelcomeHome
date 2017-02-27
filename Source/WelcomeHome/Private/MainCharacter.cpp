// Fill out your copyright notice in the Description page of Project Settings.

#include "WelcomeHome.h"
#include "Kismet/KismetMathLibrary.h"
#include "MainCharacter.h"

AMainCharacter::AMainCharacter()
{
	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	RightHandMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("RightHandMesh"));
	LeftHandMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("LeftHandMesh"));
	
	RightHandMesh->SetupAttachment(RightMotionController);
	LeftHandMesh->SetupAttachment(LeftMotionController);

	static ConstructorHelpers::FObjectFinder<UStaticMesh> CubeVisualAsset(TEXT("StaticMesh'/Game/Shapes/Shape_Cube.Shape_Cube'")); // Finds cube static mesh and sets it to CubeVisualAsset

	if (CubeVisualAsset.Succeeded())
	{
		RightHandMesh->SetStaticMesh(CubeVisualAsset.Object);
		RightHandMesh->SetWorldScale3D(FVector(0.2f, 0.2f, 0.2f));
		RightHandMesh->SetCollisionProfileName(TEXT("OverlapAll")); // We want the controller to have no collision so it is able to intersect with other actors

		LeftHandMesh->SetStaticMesh(CubeVisualAsset.Object);
		LeftHandMesh->SetWorldScale3D(FVector(0.2f, 0.2f, 0.2f));
		LeftHandMesh->SetCollisionProfileName(TEXT("OverlapAll"));
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

void AMainCharacter::SetupPlayerInputComponent(class UInputComponent* InputComponent)
{
	Super::SetupPlayerInputComponent(InputComponent);

	// Respond every frame to the values of our two movement axes, "MoveY" and "MoveX"
	InputComponent->BindAxis("MoveY", this, &AMainCharacter::MoveY);
	InputComponent->BindAxis("MoveX", this, &AMainCharacter::MoveX);

	// Grab/Drop actor input
	InputComponent->BindAction("GrabRightHand", IE_Pressed, this, &AMainCharacter::GrabRightHand);
	InputComponent->BindAction("GrabLeftHand", IE_Pressed, this, &AMainCharacter::GrabLeftHand);
	InputComponent->BindAction("GrabRightHand", IE_Released, this, &AMainCharacter::DropRightHand);
	InputComponent->BindAction("GrabLeftHand", IE_Released, this, &AMainCharacter::DropLeftHand);
	
}

void AMainCharacter::MoveY(float AxisValue)
{
	if (AxisValue >= -0.2f && AxisValue <= 0.2f) { return; } // "Joystick" deadzone

	FVector ForwardVector = RightHandMesh->GetForwardVector();
	float ScaleValue = AxisValue * MovementSpeed;

	AddMovementInput(ForwardVector, ScaleValue);

}

void AMainCharacter::MoveX(float AxisValue)
{
	if (AxisValue >= -0.2f && AxisValue <= 0.2f) { return; } // "Joystick" deadzone

	FVector RightVector = RightHandMesh->GetRightVector();
	float ScaleValue = AxisValue * MovementSpeed;

	AddMovementInput(RightVector, ScaleValue);

}

void AMainCharacter::GrabRightHand()
{
	FVector StartLocation = RightHandMesh->GetComponentLocation();
	FVector MeshForwardVector = RightHandMesh->GetForwardVector();
	FVector EndLocation = StartLocation + MeshForwardVector;

	/* Creates a trace in the shape of a sphere around the controller (probably need to adjust settings). If it is intersecting with an actor
	   it will store the actor in OutHit. 
	*/
	UKismetSystemLibrary::SphereTraceSingle_NEW
	(
		this,
		StartLocation,
		EndLocation,
		SphereTraceRadius,
		ETraceTypeQuery::TraceTypeQuery1, // Visible Trace?
		false,
		ActorsToIgnore,
		EDrawDebugTrace::ForOneFrame,
		OutHitRightHand,
		true
	);

	if (OutHitRightHand.GetActor())
	{
		// Function from VRExpansion Plugin that grips actors
		RightMotionController->GripActor
		(
			OutHitRightHand.GetActor(),
			UKismetMathLibrary::Conv_VectorToTransform(OutHitRightHand.GetActor()->GetActorLocation()),
			false,
			TEXT("None"),
			EGripCollisionType::InteractiveCollisionWithPhysics,
			EGripLateUpdateSettings::NotWhenCollidingOrDoubleGripping,
			EGripMovementReplicationSettings::ForceClientSideMovement,
			1500.0f, // Default grip stiffness
			200.0f // Default grip dampening
		);
	}

}

void AMainCharacter::GrabLeftHand()
{
	FVector StartLocation = LeftHandMesh->GetComponentLocation();
	FVector MeshForwardVector = LeftHandMesh->GetForwardVector();
	FVector EndLocation = StartLocation + MeshForwardVector;

	/* Creates a trace in the shape of a sphere around the controller (probably need to adjust settings). If it is intersecting with an actor
	it will store the actor in OutHit.
	*/
	UKismetSystemLibrary::SphereTraceSingle_NEW
	(
		this,
		StartLocation,
		EndLocation,
		SphereTraceRadius,
		ETraceTypeQuery::TraceTypeQuery1, // Visible Trace?
		false,
		ActorsToIgnore,
		EDrawDebugTrace::ForOneFrame,
		OutHitLeftHand,
		true
	);

	if (OutHitLeftHand.GetActor())
	{
		// Function from VRExpansion Plugin that grips actors
		LeftMotionController->GripActor
		(
			OutHitLeftHand.GetActor(),
			UKismetMathLibrary::Conv_VectorToTransform(OutHitLeftHand.GetActor()->GetActorLocation()),
			false,
			TEXT("None"),
			EGripCollisionType::InteractiveCollisionWithPhysics,
			EGripLateUpdateSettings::NotWhenCollidingOrDoubleGripping,
			EGripMovementReplicationSettings::ForceClientSideMovement,
			1500.0f, // Default grip stiffness
			200.0f // Default grip dampening
		);
	}

}

void AMainCharacter::DropRightHand()
{	
	if (OutHitRightHand.GetActor()) // Drop function will only be called if an actor is currently being gripped
	{
		UE_LOG(LogTemp, Warning, TEXT("Actor in hand, drop"));
		RightMotionController->DropActor
		(
			OutHitRightHand.GetActor(),
			true,
			FVector(0, 0, 0),
			FVector(0, 0, 0)
		);
	}

}

void AMainCharacter::DropLeftHand()
{
	if (OutHitLeftHand.GetActor()) // Drop function will only be called if an actor is currently being gripped
	{
		UE_LOG(LogTemp, Warning, TEXT("Actor in hand, drop"));
		LeftMotionController->DropActor
		(
			OutHitLeftHand.GetActor(),
			true,
			FVector(0, 0, 0),
			FVector(0, 0, 0)
		);
	}

}
