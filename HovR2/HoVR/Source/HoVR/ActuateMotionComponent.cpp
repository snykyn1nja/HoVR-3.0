#include "ActuateMotionComponent.h"
#include "GameFramework/Actor.h"

UActuateMotionComponent::UActuateMotionComponent()
	: enabled_(false),
	ticks_(0),
	actuateQuaternion_(),
	actuateVector_() {
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// Get the actor
	actor_ = GetOwner();
	if (!actor_) {
		UE_LOG(LogTemp, Warning, TEXT("ActuateMotionComponent: Failed to obtain Actor"));
		return;
	}

	// Get a handle to Actuate shared memory client.
	// When Actuate is installed, this library will be present in the PATH environment variable.
	hlib_ = FPlatformProcess::GetDllHandle(TEXT("libshmemclient.dll"));
	if (!hlib_) {
		UE_LOG(LogTemp, Warning, TEXT("ActuateMotionComponent: Failed to load shmemclient library"));
		return;
	}
	
	// Get reference to the send function within the library
	Send_ = (SendFunc)FPlatformProcess::GetDllExport(hlib_, TEXT("Send"));
	if (!Send_) {
		UE_LOG(LogTemp, Warning, TEXT("ActuateMotionComponent: Failed to lookup Send symbol"));
		return;
	}

	// If we got this far, then we are good to send motion data.
	enabled_ = true;
}

UActuateMotionComponent::~UActuateMotionComponent() {
	// Send a stop message to stop motion output.
	if (enabled_)
		SendStopMessage();

	// Clean up the library handle if present.
	if (hlib_)
		FPlatformProcess::FreeDllHandle(hlib_);
}

// Called when the game starts
void UActuateMotionComponent::BeginPlay() {
	Super::BeginPlay();

	// Only try to extract and send telemetry if we are enabled.
	if (!enabled_)
		return;

	// Reset time and send initialisation messages to Actuate.
	ticks_ = 0;
	SendStopMessage();
	SendConfigureTelemTypeMessage();
	SendStartMessage();
}

// Called every frame
void UActuateMotionComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) {
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// Only try to extract and send telemetry if we are enabled.
	if (!enabled_)
		return;

	// Get data about the Actor.
	FQuat unrealQuaternion = actor_->GetActorRotation().Quaternion();
	FVector unrealVector = actor_->GetVelocity();

	// Calculate time, Actuate expects milliseconds.
	ticks_ += DeltaTime * 1000.0f; 
	
	// Re-map axes for Actuate.
	// Actuate expects left handed, z-forward coordinates, and quaternions in the order w, x, y, z
	actuateVector_[0] = unrealVector.Y / 100.f;
	actuateVector_[1] = unrealVector.Z / 100.f;
	actuateVector_[2] = unrealVector.X / 100.f;
	actuateQuaternion_[0] = unrealQuaternion.W;
	actuateQuaternion_[1] = unrealQuaternion.Y;
	actuateQuaternion_[2] = unrealQuaternion.Z;
	actuateQuaternion_[3] = unrealQuaternion.X;

	// Send data to Actuate.
	SendTelemMessage();
}

// Sends a message to Actuate to stop motion output.
void UActuateMotionComponent::SendStopMessage() {
	ActuateMsg msg = {};
	msg.msgType = TELEMMSG_MSGTYPE_STOP;
	Send_(msg);
}

// Sends a message to Actuate to start motion output.
void UActuateMotionComponent::SendStartMessage() {
	ActuateMsg msg;
	msg.msgType = TELEMMSG_MSGTYPE_START;
	Send_(msg);
}

// Sends a message to Actuate to configure the type of telemetry used (acceleration or velocity).
// This plugin only ever sends velocity data.
void UActuateMotionComponent::SendConfigureTelemTypeMessage() {
	ActuateMsg msg = {};
	msg.msgType = TELEMMSG_MSGTYPE_CONFIGURETELEMTYPE;
	ActuateMsgConfigureTelemTypePayload* payload =
		reinterpret_cast<ActuateMsgConfigureTelemTypePayload*>(msg.payload);
	payload->telemType = TELEMTYPE_VELOCITY;
	Send_(msg);
}

// Sends a message to Actuate containing the telemetry data.
void UActuateMotionComponent::SendTelemMessage() {
	ActuateMsg msg = {};
	msg.msgType = TELEMMSG_MSGTYPE_TELEMETRY;
	ActuateMsgTelemPayload* payload =
		reinterpret_cast<ActuateMsgTelemPayload*>(msg.payload);
	payload->ticks = ticks_;
	payload->vector[0] = actuateVector_[0];
	payload->vector[1] = actuateVector_[1];
	payload->vector[2] = actuateVector_[2];
	payload->rotation[0] = actuateQuaternion_[0];
	payload->rotation[1] = actuateQuaternion_[1];
	payload->rotation[2] = actuateQuaternion_[2];
	payload->rotation[3] = actuateQuaternion_[3];
	Send_(msg);
}
