// Fill out your copyright notice in the Description page of Project Settings.


#include "Tank.h"
#include "GameFramework/SpringArmComponent.h"
#include "Camera/CameraComponent.h"
#include "Components/InputComponent.h"
#include "Kismet/GameplayStatics.h"


ATank::ATank()
{
    TankArm = CreateDefaultSubobject <USpringArmComponent>(TEXT("Component|Arm"));
    TankArm -> SetupAttachment(RootComponent); 

    Camera = CreateDefaultSubobject <UCameraComponent>(TEXT("Component|Camera"));
    Camera -> SetupAttachment(TankArm);

}

// Called to bind functionality to input
void ATank::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent); //super

    PlayerInputComponent->BindAxis(TEXT("MoveForward"),this,&ATank::Move); //头文件 ，BinAxis
    PlayerInputComponent->BindAxis(TEXT("Turn"),this,&ATank::Turn);

}

void ATank::Tick(float DeltaTime)
{
    
}

void ATank::Move(float Value)
{
    //Value*Speed*Deltatime
    
    FVector DeltaLocation = FVector::ZeroVector;
    DeltaLocation.X = Value * Speed * UGameplayStatics::GetWorldDeltaSeconds(this);
    AddActorLocalOffset(DeltaLocation,true);

}

void ATank::Turn(float Value)
{
    FRotator DeltaRotation = FRotator::ZeroRotator;
    DeltaRotation.Yaw = Value * Speed * UGameplayStatics::GetWorldDeltaSeconds(this);
    AddActorLocalRotation(DeltaRotation,true);
}


void ATank::BeginPlay()
{
	Super::BeginPlay();

    PlayerControllerRef = Cast<APlayerController>(GetController());
    if ( PlayerControllerRef == nullptr)
    {
        UE_LOG(LogTemp,Warning,TEXT("GetController Cast Failed"));
    }

       
}