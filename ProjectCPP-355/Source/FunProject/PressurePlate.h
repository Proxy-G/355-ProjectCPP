// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"

#include "Components/BoxComponent.h"
#include "Door.h"

#include "PressurePlate.generated.h"


UCLASS()
class FUNPROJECT_API APressurePlate : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	APressurePlate();

	//scene component for root
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
	class USceneComponent* TheRoot;

	//mesh for door
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
	class UStaticMeshComponent* TheMeshButton;

	//collider for door
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
	class UBoxComponent* Collider;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Button Stuff")
	UStaticMesh* ButtonMesh;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Button Stuff")
	float ButtonWidth = 200;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Button Stuff")
	float ButtonLength = 200;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Button Stuff")
	ADoor* ButtonInteractor;

	// Begin Overlap
	UFUNCTION()
		void BeginOverlap(UPrimitiveComponent* OverlappedComponent,
			AActor* OtherActor,
			UPrimitiveComponent* OtherComp,
			int32 OtherBodyIndex,
			bool bFromSweep,
			const FHitResult& SweepResult);

	//End Overlap
	UFUNCTION()
		void EndOverlap
		(
			UPrimitiveComponent* OverlappedComp,
			AActor* OtherActor,
			UPrimitiveComponent* OtherComp,
			int32 OtherBodyIndex
		);

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	virtual void OnConstruction(const FTransform& xform) override;
};
