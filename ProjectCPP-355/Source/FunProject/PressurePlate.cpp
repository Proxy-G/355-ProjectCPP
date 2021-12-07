// Fill out your copyright notice in the Description page of Project Settings.

#include "FunProjectCharacter.h"
#include "PressurePlate.h"


// Sets default values
APressurePlate::APressurePlate()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	TheRoot = CreateDefaultSubobject<USceneComponent>(FName("TheRoot"));
	TheRoot->SetupAttachment(RootComponent);

	TheMeshButton = CreateDefaultSubobject<UStaticMeshComponent>(FName("TheMeshButton"));
	TheMeshButton->SetupAttachment(TheRoot);

	TheMeshButton->SetStaticMesh(ButtonMesh);

	Collider = CreateDefaultSubobject<UBoxComponent>(FName("TheDoorBox"));
	Collider->SetupAttachment(TheRoot);
}

// Called when the game starts or when spawned
void APressurePlate::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void APressurePlate::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void APressurePlate::OnConstruction(const FTransform& xform)
{
	Super::OnConstruction(xform);

	TheMeshButton->SetWorldScale3D(FVector(ButtonWidth, ButtonLength, 10)/100);
	TheMeshButton->SetRelativeLocation(FVector(0,0,0));

	FVector ButtonSize = FVector(ButtonWidth, ButtonLength, 20) / 2;
	Collider->SetBoxExtent(ButtonSize);
	Collider->SetRelativeLocation(FVector(0, 0, 10));
	Collider->SetCollisionResponseToAllChannels(ECollisionResponse::ECR_Overlap);

	TheMeshButton->SetStaticMesh(ButtonMesh);

	Collider->OnComponentBeginOverlap.AddDynamic(this, &APressurePlate::BeginOverlap);
	Collider->OnComponentEndOverlap.AddDynamic(this, &APressurePlate::EndOverlap);
}

void APressurePlate::BeginOverlap(UPrimitiveComponent* OverlappedComponent,
	AActor* OtherActor,
	UPrimitiveComponent* OtherComp,
	int32 OtherBodyIndex,
	bool bFromSweep,
	const FHitResult& SweepResult)
{
	if (OtherActor != this) {
		AFunProjectCharacter* OtherChar = Cast<AFunProjectCharacter>(OtherActor);
		if (OtherChar) ButtonInteractor->ButtonOpen();
	}
}

void APressurePlate::EndOverlap (UPrimitiveComponent* OverlappedComp,
	AActor* OtherActor,
	UPrimitiveComponent* OtherComp,
	int32 OtherBodyIndex)
{
	if (OtherActor != this) {
		AFunProjectCharacter* OtherChar = Cast<AFunProjectCharacter>(OtherActor);
		if (OtherChar) ButtonInteractor->ButtonClose();

		
	}

}
