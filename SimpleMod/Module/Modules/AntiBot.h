#pragma once

#include "IModule.h"
//#include "../../../../Utils/TimerUtil.h"
//#include "../../../../Memory/Hooks.h"
class AntiBot : public IModule {
private:

public:
	AntiBot();
	~AntiBot();

	bool hitboxCheck = true;
	bool nameCheck = true;
	//bool invisibleCheck = true;
	bool entityIdCheck = true;
	//bool moveCheck = true;
	bool modeCheck = true;
	bool Serverbots = true;
	bool advanceCheck = false; //������fap, ng, �����׼���һ�����
	//bool nameCheckPlus = false;

	// Inherited via IModule
	virtual std::string getModuleName() override;
	//virtual void onWorldTick(C_GameMode*) override;
};
