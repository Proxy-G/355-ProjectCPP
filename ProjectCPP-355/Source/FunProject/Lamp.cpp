// Fill out your copyright notice in the Description page of Project Settings.

#include "Lamp.h"
#include "Components/PointLightComponent.h"
#include "Components/BoxComponent.h"

// Sets default values
ALamp::ALamp()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	TheRoot = CreateDefaultSubobject<USceneComponent>(FName("TheRoot"));
	TheRoot->SetupAttachment(RootComponent);

	TheMeshLamp = CreateDefaultSubobject<UStaticMeshComponent>(FName("TheMeshLamp"));
	TheMeshLamp->SetupAttachment(TheRoot);

	TheLampLight = CreateDefaultSubobject<UPointLightComponent>(FName("TheLampLight"));
	TheLampLight->SetupAttachment(TheMeshLamp);

	TheLampCollider = CreateDefaultSubobject<UBoxComponent>(FName("TheLampCollider"));
	TheLampCollider->SetupAttachment(TheRoot);

	ConstructorHelpers::FObjectFinder<UStaticMesh> TheCubeMesh(TEXT("/Game/Art/Meshes/1M_Cube"));
	if (TheCubeMesh.Object)
	{
		TheMeshLamp->SetStaticMesh(TheCubeMesh.Object);
		TheMeshLamp->SetWorldScale3D(FVector(10, 10, 50) / 100);

		TheLampCollider->SetBoxExtent(FVector(15,15,40));
		TheLampCollider->SetCollisionResponseToAllChannels(ECollisionResponse::ECR_Block);

		TheLampLight->SetRelativeLocation(FVector(0, 0, 50));
	}

	TheLampLight->SetIntensity(1000);
}

// Called when the game starts or when spawned
void ALamp::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ALamp::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ALamp::Interact()
{
	if (TheLampLight->Intensity == 1000)
	{
		TheLampLight->SetIntensity(0);
		if (GEngine) GEngine->AddOnScreenDebugMessage(-1, 3, FColor::Green, "Player turned off light.");
	}
	else
	{
		TheLampLight->SetIntensity(1000);
		if (GEngine) GEngine->AddOnScreenDebugMessage(-1, 3, FColor::Green, "Player turned on light.");
	}
}

