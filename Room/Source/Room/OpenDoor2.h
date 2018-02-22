// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Engine/TriggerVolume.h"
#include "Runtime/Engine/Classes/GameFramework/Actor.h"
#include "OpenDoor2.generated.h"



UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class ROOM_API UOpenDoor2 : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UOpenDoor2();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

private:
    void OpenDoor(float yaw);
    float GetTotalMassOfActorsOnPlate();
    
    UPROPERTY(EditAnywhere)
    float openAngle = -15.3f;
    
    UPROPERTY(EditAnywhere)
    ATriggerVolume* pressurePlate;
    
    UPROPERTY(EditAnywhere)
    float DoorCloseDelay = 0.53f;
    float LastDoorOpenTime;

    AActor* Owner;
	
};
