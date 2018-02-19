// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "DrawDebugHelpers.h"
#include "PhysicsEngine/PhysicsHandleComponent.h"
#include "Runtime/Engine/Classes/Components/InputComponent.h"
#include "Grabber.generated.h"


struct ULineTrace {
    FVector Start;
    FVector End;
};

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class ROOM_API UGrabber : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UGrabber();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

private:
    void Grab();
    void Release();
    void GetTrace(ULineTrace &);
    FHitResult getFirstPhysicsBodyInReach();
    
    UPROPERTY(EditAnywhere)
    float Len = 100.0f;
    
    UPhysicsHandleComponent* handle = nullptr;
    
    UInputComponent* input = nullptr;
    
    void FindComponents();
	
};
