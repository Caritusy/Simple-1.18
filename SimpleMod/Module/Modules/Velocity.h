#pragma once

#include "IModule.h"

class Velocity : public IModule {
private:
	PlayerAuthInputPacket AuthInputPacket;
public:
	float xModifier = 0.f;
	float yModifier = 0.f;
	Velocity();
	~Velocity();

	// Inherited via IModule
	virtual std::string getModuleName() override;
	virtual void onSendPacket(Packet* packet, bool& cancelSend) override;
};
