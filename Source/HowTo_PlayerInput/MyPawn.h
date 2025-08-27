// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "Camera/CameraComponent.h"
#include "MyPawn.generated.h"


UCLASS()
class HOWTO_PLAYERINPUT_API AMyPawn : public APawn
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	AMyPawn();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;


public:
	UPROPERTY(EditAnywhere)
	USceneComponent* OurVisibleComponent;
	UPROPERTY()
	UCameraComponent* OurCamera;

public:
	//Input Functions
	void Move_XAxis(float AxisValue);

	void Move_YAxis(float AxisValue);

	void StartGrowing();

	void StopGrowing();


	// Input variable
	FVector CurrentAxisPos;
	FVector CurrentVelocity;
	bool bGrowing;


	//Speed
	float MaxSpeed = 300.0f;
	float CurrentSpeed = 0.0f;

	// Grows instantly when special sequence is triggered
	bool bSpecialInputSequence = false;
};
