// Fill out your copyright notice in the Description page of Project Settings.


#include "MyCharacter.h"
#include "InputAction.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "EnhancedInputComponent.h"

// Sets default values
AMyCharacter::AMyCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AMyCharacter::BeginPlay()
{
	Super::BeginPlay();
	WalkSpeed = GetCharacterMovement()->MaxWalkSpeed;
}

// Called every frame
void AMyCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void AMyCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	UEnhancedInputComponent* EnhancedInput = Cast<UEnhancedInputComponent>(PlayerInputComponent);
	if (EnhancedInput)
	{
		if (SprintAction)
		{
			EnhancedInput->BindAction(SprintAction, ETriggerEvent::Started , this, &AMyCharacter::StartSprint);
			EnhancedInput->BindAction(SprintAction, ETriggerEvent::Completed , this, &AMyCharacter::StopSprint);
		}
		if (InteractAction)
		{
			EnhancedInput->BindAction(InteractAction, ETriggerEvent::Started , this, &AMyCharacter::Interact);
		}
	}
}

void AMyCharacter::StartSprint()
{
	bIsSprinting = true;
	GetCharacterMovement()->MaxWalkSpeed = SprintSpeed;
}

void AMyCharacter::StopSprint()
{
	bIsSprinting = false;
	GetCharacterMovement()->MaxWalkSpeed = WalkSpeed;
}

void AMyCharacter::Interact()
{
	OnInteract.Broadcast();
}