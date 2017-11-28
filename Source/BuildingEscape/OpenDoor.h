// Copyright Rachel Bood 2017

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Engine/TriggerVolume.h"
#include "OpenDoor.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class BUILDINGESCAPE_API UOpenDoor : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UOpenDoor();


protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every fsrame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

private: 
	UPROPERTY(VisibleAnywhere)
	float openAngle = 0.0f;
	float closeAngle = 90.0f;
	
	UPROPERTY(EditAnywhere)
	ATriggerVolume* pressurePlate;

	AActor* actorthatOpens;
	
	UPROPERTY(EditAnywhere)
	float doorCloseDelay = 1.0f;

	float lastDoorOpenTime;


	AActor* owner;

	void OpenDoor();
	void CloseDoor();
	
};
