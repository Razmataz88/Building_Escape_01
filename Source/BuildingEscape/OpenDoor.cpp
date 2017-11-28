// Copyright Rachel Bood 2017

#include "OpenDoor.h"
#include "Gameframework/Actor.h"


// Sets default values for this component's properties
UOpenDoor::UOpenDoor()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UOpenDoor::BeginPlay()
{
	Super::BeginPlay();
	actorthatOpens = GetWorld()->GetFirstPlayerController()->GetPawn();
	owner = GetOwner();
	
}

void UOpenDoor::OpenDoor()
{
	owner->SetActorRotation(FRotator(0.0f, openAngle, 0.0f));
}

void UOpenDoor::CloseDoor()
{
	owner->SetActorRotation(FRotator(0.0f, closeAngle, 0.0f));
}

// Called every frame
void UOpenDoor::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	if (pressurePlate->IsOverlappingActor(actorthatOpens))
	{
		OpenDoor();
		lastDoorOpenTime = GetWorld()->GetTimeSeconds();
	}

	if (GetWorld()->GetTimeSeconds() - lastDoorOpenTime > doorCloseDelay)
	{
		CloseDoor();
	}
	// Check if it is time to close the door 
}



