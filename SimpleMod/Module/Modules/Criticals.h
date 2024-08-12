#pragma once
#include "IModule.h"
#include "../ModuleManager.h"
class Criticals:public IModule
{
private:
	int hurttime = 10;
	int CPS = 5;
	TimerUtil CPSTime;
	PlayerActionPacket PlayerAction;
public:

	Criticals();
	~Criticals();

	virtual std::string getModuleName() override;
	virtual void onSendPacket(Packet* packet, bool& cancelSend) override;
	virtual void onAttack(Entity* attackEnt) override;
};

