#pragma once
#include "IModule.h"
#include "../ModuleManager.h"
#include "../../../Utils/TimerUtil.h"
class built:public IModule{
private:

	
	float delay = 20.f;
	TimerUtil delayTime;
//	std::string path = "";
	CommandRequestPacket commandrequest;
public:

	//inline std::string& getpath() { return path; };
	inline float& getDelay() { return delay; };

	built();
	~built();

	virtual std::string getModuleName() override;
	virtual void onTick(GameMode* gm) override;
	virtual void onDisable() override;
	virtual void onEnable() override;
};

