#pragma once
#include "IModule.h"
class Reach:public IModule{
private:
	float reachValue = 7.f;
	float* reachPtr = nullptr;
	float originalReach = 0;
	unsigned long oldProtect = 0;
public:
	Reach();
	~Reach();

	virtual std::string getModuleName() override;
	virtual void onEnable() override;
	virtual void onDisable() override;
	virtual void onTick(GameMode* gm) override;
};

