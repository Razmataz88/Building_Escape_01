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
	UE_LOG(LogTemp, Warning, TEXT("Grabber reporting for duty!"));
	// ...
	
}


// Called every frame
void UGrabber::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
	FVector playerViewpointLocation;
	FRotator playerViewpointRotation;
	GetWorld()->GetFirstPlayerController()->GetPlayerViewPoint(
								OUT playerViewpointLocation, 
								OUT playerViewpointRotation);

	/*FString objectName = GetOwner()->GetName();
	FString objectPos = location.ToString();
	UE_LOG(LogTemp, Warning, TEXT("%s is at %s!"), *objectName, *objectPos);*/
	
	FVector lineTraceEnd = playerViewpointLocation + playerViewpointRotation.Vector() * reach;

	DrawDebugLine(GetWorld(), playerViewpointLocation, lineTraceEnd, FColor(255, 0, 0), false, 0.0f, 0.0f, 20.0f);
}


