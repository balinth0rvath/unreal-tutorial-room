// Fill out your copyright notice in the Description page of Project Settings.

#include "Grabber.h"


// Sets default values for this component's properties
UGrabber::UGrabber()
{
	PrimaryComponentTick.bCanEverTick = true;
}

// Called when the game starts
void UGrabber::BeginPlay()
{
	Super::BeginPlay();
	UE_LOG(LogTemp, Warning, TEXT("Grabber here"));
    FindComponents();
}

void UGrabber::FindComponents()
{
    handle = GetOwner()->FindComponentByClass<UPhysicsHandleComponent>();
    input = GetOwner()->FindComponentByClass<UInputComponent>();
    if (handle!=nullptr && input!=nullptr)
    {
        input->BindAction("Grab", IE_Pressed, this, &UGrabber::Grab);
        input->BindAction("Grab", IE_Released, this, &UGrabber::Release);
    } else
    {
        UE_LOG(LogTemp, Error, TEXT("Handler or input missing: %s %s"), *GetOwner()->GetName());
    }
}

void UGrabber::Grab()
{
    auto result = getFirstPhysicsBodyInReach();
    auto ComponentToGrab = result.GetComponent();
    auto ActorHit = result.GetActor();
    if (ActorHit)
    {
        handle->GrabComponent(ComponentToGrab,NAME_None,ComponentToGrab->GetOwner()->GetActorLocation(),true);
    }
}

void UGrabber::Release()
{
    handle->ReleaseComponent();
}

FHitResult UGrabber::getFirstPhysicsBodyInReach()
{
    
    FHitResult lineTraceHit;
    FCollisionObjectQueryParams q;
    ULineTrace LineTrace;
    GetTrace(LineTrace);
    GetWorld()->LineTraceSingleByObjectType(lineTraceHit,LineTrace.Start, LineTrace.End,
        FCollisionObjectQueryParams(ECollisionChannel::ECC_PhysicsBody),
        FCollisionQueryParams(FName(TEXT("")),false,GetOwner()));
    
    return lineTraceHit;
}

void UGrabber::GetTrace(ULineTrace & LineTrace)
{
    FVector Vector;
    FRotator Rotator;
    GetWorld()->GetFirstPlayerController()->GetPlayerViewPoint(Vector, Rotator);
    LineTrace.Start = Vector;
    LineTrace.End = Vector + (this->Len) * Rotator.Vector();
    return;
}

// Called every frame
void UGrabber::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
    
    if (handle->GrabbedComponent)
    {
        ULineTrace LineTrace;
        GetTrace(LineTrace);
        handle->SetTargetLocation(LineTrace.End);
    }
}

