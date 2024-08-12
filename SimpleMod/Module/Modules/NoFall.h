#pragma once
#include "IModule.h"
#include "../../../Utils/TimerUtil.h"
class NoFall:public IModule{
private:
	float delay = 20.f;
	TimerUtil delayTime;
	PlayerActionPacket PlayerAction;
	PlayerAuthInputPacket PlayerAuthInput;
public:
	NoFall();
	~NoFall();

	// Inherited via IModule
	virtual std::string getModuleName() override;
	virtual void onSendPacket(Packet* packet, bool& cancelSend) override;
	virtual void onTick(GameMode* gm) override;
};

