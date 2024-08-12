#pragma once

#include "IModule.h"

class Crasher : public IModule {
private:
	SettingEnum mode;

	PlayerAuthInputPacket PlayerAuthInput;
	C_MovePlayerPacket movePacket;
	LevelSoundEventPacket soundEventPacket;
public:
	Crasher();
	~Crasher();

	// Inherited via IModule
	virtual std::string getModuleName() override;
	virtual void onSendPacket(Packet* packet, bool& cancelSend) override;
	virtual void onEnable() override;
	virtual void onTick(GameMode* gm) override;
};
