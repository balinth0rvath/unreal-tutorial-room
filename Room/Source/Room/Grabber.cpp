// Fill out your copyright notice in the Description page of Project Settings.

#include "Grabber.h"


// Sets default values for this component's properties
UGrabber::UGrabber()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UGrabber::BeginPlay()
{
	Super::BeginPlay();

	UE_LOG(LogTemp, Warning, TEXT("Grabber here"));
    this->PlayerController = GetWorld()->GetFirstPlayerController();
	
}


// Called every frame
void UGrabber::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
    FVector vector;
    FRotator rotator;
    this->PlayerController->GetPlayerViewPoint(vector, rotator);
    FString v = vector.ToString();
    FString r = rotator.ToString();
    
    FVector lineTraceEnd = rotator.Vector();
    
    FString r2v = lineTraceEnd.ToString();
    
    //UE_LOG(LogTemp, Warning, TEXT("Grabber here %s : %s r2v: %s"), *v, *r, *r2v);
    
	// ...
    
    
    DrawDebugLine(GetWorld(), vector, vector + (this->Len) * lineTraceEnd, FColor(255,0,0), false, 0.0f,0.0f,10.0f);
    
    FHitResult lineTraceHit;
    FCollisionObjectQueryParams q;
    GetWorld()->LineTraceSingleByObjectType(lineTraceHit,vector, vector + (this->Len) * lineTraceEnd,
                                            FCollisionObjectQueryParams(ECollisionChannel::ECC_PhysicsBody),
                                            FCollisionQueryParams(FName(TEXT("")),false,GetOwner())
                                            );
    if (lineTraceHit.GetActor() != NULL)
    {
        AActor* a = lineTraceHit.GetActor();
        FString name = a->GetName();
        UE_LOG(LogTemp, Warning, TEXT("Collision with %s"), *name);
    }
}

