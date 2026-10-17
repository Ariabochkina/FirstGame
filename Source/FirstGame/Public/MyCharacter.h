// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "MyCharacter.generated.h"

class UInputAction;

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnInteractSignature);

UCLASS()
class FIRSTGAME_API AMyCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AMyCharacter();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Input")
	UInputAction* SprintAction = nullptr;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Input")
	UInputAction* InteractAction = nullptr;
	
	UPROPERTY(BlueprintReadOnly)
	bool bIsSprinting = false;
	
	void StartSprint();
	void StopSprint();
	void Interact();
	
	UPROPERTY(BlueprintAssignable)
	FOnInteractSignature OnInteract;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	float SprintSpeed = 900.0f;
	
	float WalkSpeed = 500.0f;
};
