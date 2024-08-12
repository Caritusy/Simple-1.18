#pragma once
#include "IModule.h"
#include "../../../Utils/TimerUtil.h"
class Derp:public IModule{
private:
	int counter = 0;
	float delay = 200;
	bool epicStroke = true;
	bool epicsquat = false;
	bool packetMode = false;
	TimerUtil delayTime;
	PlayerActionPacket PlayerAction;
	PlayerAuthInputPacket AuthInputPacket;
public:
	Derp();
	~Derp();

	// Inherited via IModule
	virtual void onTick(GameMode* gm) override;
	virtual std::string getModuleName() override;
	virtual void onSendPacket(Packet* packet, bool& cancelSend) override;
};

