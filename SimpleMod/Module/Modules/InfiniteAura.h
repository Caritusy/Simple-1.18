#pragma once

#include "IModule.h"
#include "../ModuleManager.h"
#include "../../../Utils/TimerUtil.h"

class InfiniteAura : public IModule {
private:
	int CPS = 5;
	TimerUtil CPSTime;
	float tpDistance = 5.f;
	SettingEnum mode;
	//SettingEnum packetMode;
	std::vector<Vec3> posList = {};
	bool renderPos = true;
	PlayerAuthInputPacket AuthInputPacket;
public:
	std::vector<Entity*> targetList = {};
	float range = 100.f;

	InfiniteAura();
	~InfiniteAura();

	// Inherited via IModule
	virtual std::string getModuleName() override;
	virtual void onTick(GameMode* gm) override;
//	virtual void onPreRender(C_MinecraftUIRenderContext* renderCtx) override;
	virtual void onEnable() override;
	virtual void onSendPacket(Packet* packet, bool& cancelSend) override;
};
