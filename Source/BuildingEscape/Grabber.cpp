// Copyright Rachel Bood 2017

#include "Grabber.h"
#include "Gameframework/Actor.h"
#include "DrawDebugHelpers.h"

#define OUT

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
	FindPhysicsHandleComponent();
	SetupAttachedInputComponent();
}

void UGrabber::FindPhysicsHandleComponent()
{
	/// Look for attached Physics Handle
	physicsHandle = GetOwner()->FindComponentByClass<UPhysicsHandleComponent>();
	if (!physicsHandle)
	{
		UE_LOG(LogTemp, Error, TEXT("Cannot grab PhysicsHandler on %s"), *(GetOwner()->GetName()));
		physicsHandle = nullptr;
	}

}

void UGrabber::SetupAttachedInputComponent()
{
	/// Look for attached input component (only appears at runtime)
	inputComponent = GetOwner()->FindComponentByClass<UInputComponent>();
	if (inputComponent)
	{
		UE_LOG(LogTemp, Warning, TEXT("Found Input Component on %s"), *(GetOwner()->GetName()));
		/// Bind the input axis
		inputComponent->BindAction("Grab", IE_Pressed, this, &UGrabber::Grab);
		inputComponent->BindAction("Grab", IE_Released, this, &UGrabber::Release);
	}
}

void UGrabber::Grab()
{
	if (!physicsHandle) { return; }
	/// LINE TRACE and see if we reach any actors with physics body collision channel set
	auto hitResult = GetFirstPhysicsBodyInReach();
	auto ComponentToGrab = hitResult.GetComponent();
	auto ActorHit = hitResult.GetActor();

	/// If we hit something then attach a physics handle
	if (ActorHit != nullptr)
	{
		physicsHandle->GrabComponentAtLocationWithRotation(
			ComponentToGrab, 
			NAME_None, // no bones needed
			ComponentToGrab->GetOwner()->GetActorLocation(),
			ComponentToGrab->GetOwner()->GetActorRotation()
		);
	}
}

void UGrabber::Release()
{
	// release physics handle
	if (physicsHandle)
	{
		physicsHandle->ReleaseComponent();
	}
}

// Called every frame
void UGrabber::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	if (!physicsHandle) { return; }
	// if the physics handle is attached
	if (physicsHandle->GrabbedComponent)
	{
		// move the object that we're holding
		physicsHandle->SetTargetLocation(GetPlayerReachLineEnd());
	}
}

const FHitResult UGrabber::GetFirstPhysicsBodyInReach()
{
	/// Get player view point this tick

	/// Line-trace (AKA ray-cast) out to reach distance
	FHitResult hitResult;

	/// Setupquery parameters
	FCollisionQueryParams TraceParameters(FName(TEXT("")), false, GetOwner());
	GetWorld()->LineTraceSingleByObjectType(
		OUT hitResult,
		GetPlayerReachLineStart(),
		GetPlayerReachLineEnd(),
		FCollisionObjectQueryParams(ECollisionChannel::ECC_PhysicsBody),
		TraceParameters);
	return hitResult;
}

FVector UGrabber::GetPlayerReachLineStart()
{
	FVector playerViewpointLocation;
	FRotator playerViewpointRotation;
	GetWorld()->GetFirstPlayerController()->GetPlayerViewPoint(
		OUT playerViewpointLocation,
		OUT playerViewpointRotation);

	return playerViewpointLocation;
}

FVector UGrabber::GetPlayerReachLineEnd()
{
	/// Get player view point this tick
	FVector playerViewpointLocation;
	FRotator playerViewpointRotation;
	GetWorld()->GetFirstPlayerController()->GetPlayerViewPoint(
		OUT playerViewpointLocation,
		OUT playerViewpointRotation);

	return playerViewpointLocation + playerViewpointRotation.Vector() * reach;
}


