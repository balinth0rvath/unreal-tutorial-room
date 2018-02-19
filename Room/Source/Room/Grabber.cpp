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
    UE_LOG(LogTemp, Warning, TEXT("Grab"));
    FHitResult result = getFirstPhysicsBodyInReach();
    auto ComponentToGrab = result.GetComponent();
    auto ActorHit = result.GetActor();
    if (ActorHit)
    {
        handle->GrabComponent(ComponentToGrab,NAME_None,ComponentToGrab->GetOwner()->GetActorLocation(),true);
    }
}

void UGrabber::Release()
{
    UE_LOG(LogTemp, Warning, TEXT("Release"));
    handle->ReleaseComponent();
}

FHitResult UGrabber::getFirstPhysicsBodyInReach()
{
    FVector vector;
    FRotator rotator;
    this->PlayerController->GetPlayerViewPoint(vector, rotator);
    FString v = vector.ToString();
    FString r = rotator.ToString();
    
    FVector lineTraceEnd = rotator.Vector();
    
    FString r2v = lineTraceEnd.ToString();
    
    //UE_LOG(LogTemp, Warning, TEXT("Grabber here %s : %s r2v: %s"), *v, *r, *r2v);
    
    // ...
    
    
    //DrawDebugLine(GetWorld(), vector, vector + (this->Len) * lineTraceEnd, FColor(255,0,0), false, 0.0f,0.0f,10.0f);
    
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
    return lineTraceHit;
}

// Called every frame
void UGrabber::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
    
    if (handle->GrabbedComponent)
    {
        FVector vector;
        FRotator rotator;
        this->PlayerController->GetPlayerViewPoint(vector, rotator);
        FVector ev = rotator.Vector();
        FVector lineTraceEnd =vector + (this->Len) * ev;
        
        handle->SetTargetLocation(lineTraceEnd);
    }
}

