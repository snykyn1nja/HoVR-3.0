#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "ActuateMotionComponent.generated.h"

#define TELEMMSG_MSGTYPE_START 0
#define TELEMMSG_MSGTYPE_STOP 1
#define TELEMMSG_MSGTYPE_TELEMETRY 2
#define TELEMMSG_MSGTYPE_CONFIGURETELEMTYPE 3

#define TELEMTYPE_VELOCITY 0

struct ActuateMsg {
	int msgType;
	char payload[64];
};

struct ActuateMsgConfigureTelemTypePayload {
	int telemType;
};

struct ActuateMsgTelemPayload {
	unsigned long long ticks;
	float vector[3];
	float engineRpm;
	float rotation[4];
	float fuelLevel;
	float temperature;
	float tripCounter;
	float gearIndicator;
	unsigned char dashLights;
};

// send function prototype
typedef void(*SendFunc)(ActuateMsg&);

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class HoVR_API UActuateMotionComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UActuateMotionComponent();
	~UActuateMotionComponent();

	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

	AActor* actor_;
	unsigned long long ticks_;
	float actuateQuaternion_[4];
	float actuateVector_[3];

private:
	void SendStopMessage();
	void SendStartMessage();
	void SendConfigureTelemTypeMessage();
	void SendTelemMessage();

	bool enabled_;
	SendFunc Send_;
	void* hlib_;
};
