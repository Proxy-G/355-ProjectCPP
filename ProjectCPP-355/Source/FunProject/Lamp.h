// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Components/BoxComponent.h"

#include "UObject/ConstructorHelpers.h"
#include "InteractableThing.h"

#include "Lamp.generated.h"

UCLASS()
class FUNPROJECT_API ALamp : public AActor, public IInteractableThing
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ALamp();

	//scene component for root
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
		class USceneComponent* TheRoot;

	//mesh for lamp
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
		class UStaticMeshComponent* TheMeshLamp;

	//light for lamp
	UPROPERTY(VisibleAnywhere, Category = "Components")
	class UPointLightComponent* TheLampLight;

	//collider for lamp
	UPROPERTY(VisibleAnywhere, Category = "Components")
	class UBoxComponent* TheLampCollider;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	virtual void Interact();


};
