// Fill out your copyright notice in the Description page of Project Settings.

#include "OpenDoor2.h"


// Sets default values for this component's properties
UOpenDoor2::UOpenDoor2()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}



void UOpenDoor2::OpenDoor(float yaw)
{
    AActor* Owner = GetOwner();
    
    FRotator rotation = Owner->GetActorRotation();
    FRotator newRotation(0.f,yaw,0.f);
    //UE_LOG(LogTemp, Error, TEXT("Old rotation_is: %s"), *rotation.ToString());
    Owner->SetActorRotation(newRotation, ETeleportType::None);
    
}

// Called when the game starts
void UOpenDoor2::BeginPlay()
{
	Super::BeginPlay();
    this->actorThatOpens = GetWorld()->GetFirstPlayerController()->GetPawn();
    
	
}


// Called every frame
void UOpenDoor2::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

    if (pressurePlate->IsOverlappingActor(actorThatOpens)) {
        UE_LOG(LogTemp, Error, TEXT("OPEN IT"));
        OpenDoor(53);
    }
}

