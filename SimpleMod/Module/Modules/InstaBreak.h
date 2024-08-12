#pragma once

#include "IModule.h"

class InstaBreak : public IModule {
private:
	int tick = 0;
	PlayerActionPacket actionPacket;
public:
	SettingEnum mode;

	InstaBreak();
	~InstaBreak();

	// Inherited via IModule
	virtual std::string getModuleName() override;
	virtual void onTick(GameMode* gm) override;
};
