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
    Owner->SetActorRotation(FRotator(0.f,yaw,0.f));
}

// Called when the game starts
void UOpenDoor2::BeginPlay()
{
	Super::BeginPlay();
    this->actorThatOpens = GetWorld()->GetFirstPlayerController()->GetPawn();
    this->Owner = GetOwner();
	
}


// Called every frame
void UOpenDoor2::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

    if (pressurePlate->IsOverlappingActor(actorThatOpens)) {
        if (LastDoorOpenTime==0)
            UE_LOG(LogTemp, Error, TEXT("OPEN IT"));
        OpenDoor(openAngle);
        LastDoorOpenTime =  GetWorld()->GetTimeSeconds();
        UE_LOG(LogTemp, Error, TEXT("KEEP OPEN IT"));
    }
    
    float currentTime = GetWorld()->GetTimeSeconds();
    if ((currentTime - LastDoorOpenTime > DoorCloseDelay) && (LastDoorOpenTime!=0))
    {
        UE_LOG(LogTemp, Error, TEXT("CLOSE IT"));
        OpenDoor(-90.f);
        LastDoorOpenTime = 0;
    }
    
    // Check if it is time to close the door;
}

