// Fill out your copyright notice in the Description page of Project Settings.


#include "Door.h"

// Sets default values
ADoor::ADoor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	TheRoot = CreateDefaultSubobject<USceneComponent>(FName("TheRoot"));
	TheRoot->SetupAttachment(RootComponent);

	TheHinge = CreateDefaultSubobject<USceneComponent>(FName("TheHinge"));
	TheHinge->SetupAttachment(TheRoot);

	Collider = CreateDefaultSubobject<UBoxComponent>(FName("TheDoorBox"));
	Collider->SetupAttachment(TheRoot);

	TheMeshDoor = CreateDefaultSubobject<UStaticMeshComponent>(FName("TheMeshDoor"));
	TheMeshDoor->SetupAttachment(TheHinge);

	TheMeshFrame = CreateDefaultSubobject<UInstancedStaticMeshComponent>(FName("TheMeshFrame"));
	TheMeshFrame->SetupAttachment(TheRoot);

	DoorAnim = CreateDefaultSubobject<UTimelineComponent>(FName("DoorAnim"));


}

void ADoor::OnAnimUpdate(float val)
{
	FRotator rot(0, val * 90, 0);
	if (IsDoorFlipped) rot.Yaw *= -1;
	
	TheHinge->SetRelativeRotation(rot);
}

// Called when the game starts or when spawned
void ADoor::BeginPlay()
{
	Super::BeginPlay();
	
	if (DoorOpenCurve)
	{
		FOnTimelineFloat eventHandler;
		eventHandler.BindUFunction(this, TEXT("OnAnimUpdate"));
		DoorAnim->AddInterpFloat(DoorOpenCurve, eventHandler, FName("Handle Curve Func"));
		DoorAnim->SetTimelineLengthMode(ETimelineLengthMode::TL_LastKeyFrame); //set to use last keyframe as length of timeline
	}
}

// Called every frame
void ADoor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void ADoor::OnConstruction(const FTransform& xform)
{
	Super::OnConstruction(xform);

	TheMeshDoor->SetWorldScale3D(FVector(WidthOfDoor, DepthOfDoor, HeightOfDoor)/100);
	TheMeshDoor->SetRelativeLocation(FVector(WidthOfDoor / 2, 0, HeightOfDoor / 2));
	TheHinge->SetRelativeLocation(FVector(-WidthOfDoor / 2, 0, 0));

	FVector DoorSize = FVector(WidthOfDoor, DepthOfDoor, HeightOfDoor) / 2;
	Collider->SetBoxExtent(DoorSize);
	Collider->SetRelativeLocation(FVector(0, 0, HeightOfDoor / 2));
	Collider->SetCollisionResponseToChannel(ECollisionChannel::ECC_Visibility, ECollisionResponse::ECR_Block);

	TheMeshDoor->SetStaticMesh(DoorMesh);
	TheMeshFrame->SetStaticMesh(DoorMesh);

	TheMeshFrame->ClearInstances();
	TheMeshFrame->AddInstance(FTransform(FRotator(0, 0, 0), FVector(WidthOfDoor / 2 + DepthOfDoor / 2, 0, HeightOfDoor / 2), FVector(DepthOfDoor * 1.25f, DepthOfDoor * 1.25f, HeightOfDoor) / 100));
	TheMeshFrame->AddInstance(FTransform(FRotator(0, 0, 0), FVector(-WidthOfDoor / 2 - DepthOfDoor / 2, 0, HeightOfDoor / 2), FVector(DepthOfDoor * 1.25f, DepthOfDoor * 1.25f, HeightOfDoor) / 100));
}

void ADoor::Interact()
{
	if (!InteractByButton)
	{
		if (GEngine) GEngine->AddOnScreenDebugMessage(-1, 3, FColor::Green, "Player interacted with door.");

		if (IsDoorOpen)
		{
			DoorAnim->Reverse();
			IsDoorOpen = false;
		}
		else
		{
			//TODO: Determine what side the player is one to set IsDoorFlipped
			ACharacter* Player = UGameplayStatics::GetPlayerCharacter(GetWorld(), 0);

			FVector VecToDoor = GetActorLocation() - Player->GetActorLocation();
			VecToDoor.Normalize();

			float align = FVector::DotProduct(VecToDoor, GetActorRightVector());
			IsDoorFlipped = (align < 0);

			DoorAnim->Play();
			IsDoorOpen = true;
		}
	}
}

void ADoor::ButtonOpen()
{
	if (InteractByButton)
	{
		if (!IsDoorOpen)
		{
			if (GEngine) GEngine->AddOnScreenDebugMessage(-1, 3, FColor::Green, "Button pressed. Door open.");
			
			DoorAnim->Play();
			IsDoorOpen = true;
		}
	}
}

void ADoor::ButtonClose()
{
	if (InteractByButton)
	{
		if (IsDoorOpen)
		{
			if (GEngine) GEngine->AddOnScreenDebugMessage(-1, 3, FColor::Green, "Button not pressed. Door closed.");
			
			DoorAnim->Reverse();
			IsDoorOpen = false;
		}
	}
}

