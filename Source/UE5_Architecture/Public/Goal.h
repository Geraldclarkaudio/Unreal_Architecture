// Fill out your copyright notice in the Description page of Project Settings.

//TODO: 1. Notify goal that it has been landed on by the ship. 
//		2. Stop a timer. 
//		3. Activate celebration vfx. 

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Goal.generated.h"

UCLASS()
class UE5_ARCHITECTURE_API AGoal : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AGoal();
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	virtual void NotifyHit(UPrimitiveComponent* MyComp,
		AActor* Other, 
		UPrimitiveComponent* OtherComp,
		bool bSelfMoved,
		FVector HitLocation,
		FVector HitNormal,
		FVector NormalImpulse,
		const FHitResult& Hit) override;

	bool bGameOver;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

};
