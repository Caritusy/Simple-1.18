#pragma once
#include "IModule.h"
#include "../ModuleManager.h"
#include "../../../Utils/TimerUtil.h"
class TpAura:public IModule{
private:
	float delay = 100;
	int Odelay = 0;
	int turn = 0;
	bool lerp = true;
	SettingEnum position;
public:
	TimerUtil time;
	float range = 3;

	TpAura();
	~TpAura();

	// Inherited via IModule
	virtual std::string getModuleName() override;
	virtual void onTick(GameMode* gm) override;
	virtual void onEnable() override;
};

