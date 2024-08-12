#pragma once
#include "IModule.h"
#include "../ModuleManager.h"
class Killaura:public IModule{
private:
	float FOV = 360.f;
	bool isMulti = true;
	int CPS = 5;
	int maxCPS = 20;
	int minCPS = 20;
	TimerUtil CPSTime;
	bool autoweapon = false;
	bool SimulateCPS = true;
	bool silent = true;
	PlayerAuthInputPacket AuthInputPacket;


	friend void findEntity(Entity* currentEntity, bool isRegularEntity);
public:

	bool rotations = true;
	bool targetListEmpty = true;
	Vec2 angle;
	bool isMobAura = false;
	bool hurttime = true;
	float range = 7;

	Killaura();
	~Killaura();

	virtual std::string getModuleName() override;
	virtual void onTick(GameMode* gm) override;
	virtual void onEnable() override;
	virtual void onSendPacket(Packet* packet, bool& cancelSend) override;
};

