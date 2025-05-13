// Fill out your copyright notice in the Description page of Project Settings.
#include "Ship.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"

// Sets default values
AShip::AShip()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	//to contruct a component, lets use the constructor.. 
	//set up component as a sub object (UStaticMeshComponent) and name it ShipMesh
	shipMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("ShipMesh"));
	//Root Component MUST BE OF THE USCENECOMPONENT... 
	SetRootComponent(shipMesh); 
	//make a camera boom object and make it a child of the shipMesh
	cameraBoom = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraBoom"));
	cameraBoom->SetupAttachment(shipMesh);
	camera = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
	camera->SetupAttachment(cameraBoom);
	//***IMPORTANT***
	cameraBoom->TargetArmLength = 1000.f; // this will only effect the value on a newly constructed object. 
	//auto possess player 0
	AutoPossessPlayer = EAutoReceiveInput::Player0;
}

// Called when the game starts or when spawned
void AShip::BeginPlay()
{
	Super::BeginPlay();	

	//get player controller and store it. 
	if (APlayerController* PlayerController = Cast<APlayerController>(GetController())) {
		//get sub system/ 
		if (UEnhancedInputLocalPlayerSubsystem* subSystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>
			(PlayerController->GetLocalPlayer())) 
		{
			subSystem->AddMappingContext(shipMappingContext, 0);
		}
	}
}

// Called every frame
void AShip::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

// Called to bind functionality to input
void AShip::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	if (UEnhancedInputComponent* EnhancedInputComponent = CastChecked<UEnhancedInputComponent>(PlayerInputComponent)) {
		
		//bind actions to a function. 
		EnhancedInputComponent->BindAction(propelUpAction, ETriggerEvent::Triggered, this, &AShip::PropelUp);
		EnhancedInputComponent->BindAction(rotateAction, ETriggerEvent::Triggered, this, &AShip::RotateShip);
	}

}

void AShip::NotifyHit(class UPrimitiveComponent* MyComp, AActor* Other, class UPrimitiveComponent* OtherComp,
	bool bSelfMoved, FVector HitLocation, FVector HitNormal, FVector NormalImpulse, const FHitResult& Hit)
{
	Super::NotifyHit(MyComp, Other, OtherComp, bSelfMoved, HitLocation, HitNormal, NormalImpulse, Hit);
	if (isLandedSafely())
	{
		UE_LOG(LogTemp, Warning, TEXT("Ship landed safely"));
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("Ship not landed safely"));
	}
}

bool AShip::isLandedSafely()
{
	FRotator currentRot = GetActorRotation();
	float acceptableRollRange = 80.f;
	return FMath::Abs(currentRot.Roll) <= acceptableRollRange;
}

void AShip::PropelUp(const FInputActionValue& Value) {
	
	//get what the value is 
	bool currentValue = Value.Get<bool>();

	if (currentValue) {
		//create an impulse. Need to store the impulse in a variable 
		const FVector worldImpulse = FVector(0, 0, 1) * impulseStrength;
		const FVector localImpulse = GetActorRotation().RotateVector(worldImpulse);
		shipMesh->AddImpulse(localImpulse, NAME_None, true);
	}
}

void AShip::RotateShip(const FInputActionValue& Value)
{
	if (float currentValue = Value.Get<float>()) {
		const FVector Torque = FVector(1, 0, 0) * currentValue * torqueStrength;
		shipMesh->AddTorqueInRadians(Torque, NAME_None, true);
	}
}

