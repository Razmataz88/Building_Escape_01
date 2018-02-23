// Copyright Rachel Bood 2017

#include "OpenDoor.h"
#include "Components/PrimitiveComponent.h"
#include "Gameframework/Actor.h"

#define OUT

// Sets default values for this component's properties
UOpenDoor::UOpenDoor()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;
	if (pressurePlate)
	{
		UE_LOG(LogTemp, Error, TEXT("Cannot grab pressureplate on %s"), *(GetOwner()->GetName()));
		pressurePlate = nullptr;
	}
	// ...
}


// Called when the game starts
void UOpenDoor::BeginPlay()
{
	Super::BeginPlay();
	owner = GetOwner();
	if (!owner)
	{
		UE_LOG(LogTemp, Error, TEXT("Cannot grab owner"));
		owner = nullptr;
	}
	
}

// Called every frame
void UOpenDoor::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
	
	// Pull the Trigger Volume
	if (GetTotalMassOfActorsOnPlate() > threshold)
	{
		OnOpen.Broadcast();
	}
	else
	{
		OnClose.Broadcast();
	}
}

float UOpenDoor::GetTotalMassOfActorsOnPlate()
{
	float totalMass = 0.0f;

	if (!pressurePlate) { return totalMass; }

	TArray<AActor*> overlappingActors;

	// Find all the overlapping actors
	pressurePlate->GetOverlappingActors(OUT overlappingActors);

	// Iterate through them adding their masses
	for (const auto* actor: overlappingActors)
	{
		UE_LOG(LogTemp, Warning, TEXT("%s"), *(actor->GetName()));
		totalMass += actor->FindComponentByClass<UPrimitiveComponent>()->GetMass();
	}
	return totalMass;
}

