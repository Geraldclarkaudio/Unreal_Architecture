// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "GameFramework/SpringArmComponent.h"
#include "Camera/CameraComponent.h"
#include "InputActionValue.h"
#include "Ship.generated.h"


//forward declaration
class UInputMappingContext;
class UInputAction;

UCLASS()
class UE5_ARCHITECTURE_API AShip : public APawn
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	AShip();
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Ship | Input")
	float impulseStrength = 10.f;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Ship | Movement")
	float torqueStrength = 10.f;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Ship | Graphics")
	//component type to add * at the end of the type  
	UStaticMeshComponent* shipMesh;
	//INPUT STUFF
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Ship | Input")
	UInputMappingContext* shipMappingContext; 
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Ship | Input")
	UInputAction* propelUpAction; // space bar

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Ship | Input")
	UInputAction* rotateAction; // a and D

	//functions 
	// the value type needs to be const since BindAction method of the EnhancedInputComponent class uses a const FInputActionValue as its first parameter. 
	void PropelUp(const FInputActionValue& Value);
	void RotateShip(const FInputActionValue& Value);
	

private:
	UPROPERTY(VisibleAnywhere)
	//camera boom system 
	USpringArmComponent* cameraBoom;
	UPROPERTY(VisibleAnywhere)
	UCameraComponent* camera;
};
