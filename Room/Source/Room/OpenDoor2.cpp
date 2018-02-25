// Fill out your copyright notice in the Description page of Project Settings.

#include "OpenDoor2.h"
#define OUT


// Sets default values for this component's properties
UOpenDoor2::UOpenDoor2()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}




// Called when the game starts
void UOpenDoor2::BeginPlay()
{
	Super::BeginPlay();
    
    this->Owner = GetOwner();
    
    if (!pressurePlate)
    {
        UE_LOG(LogTemp, Error, TEXT("Missing pressure plate: %s"), *GetOwner()->GetName());
        return;
    }
	
}


// Called every frame
void UOpenDoor2::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

    if (!pressurePlate)
        return;
    if (GetTotalMassOfActorsOnPlate()>TriggerMass)
    {
        OnOpen.Broadcast();
    }
    else
    {
        OnClose.Broadcast();
    }
}

float UOpenDoor2::GetTotalMassOfActorsOnPlate()
{
    float TotalMass = 0.f;
    TArray<AActor*> OverlappingActors;
    pressurePlate->GetOverlappingActors(OUT OverlappingActors);
    for(const auto& Actor : OverlappingActors)
    {
        TotalMass+=Actor->FindComponentByClass<UPrimitiveComponent>()->GetMass();
        UE_LOG(LogTemp, Warning, TEXT("Mass: %s"), *Actor->GetName());
    }
    return TotalMass;
}
