#pragma once

#include "../ModuleManager.h"
#include "IModule.h"

class Scaffold : public IModule {
private:
	PlayerAuthInputPacket PlayerAuthInput;
	SettingEnum mode;

	SettingEnum rotations;
	Vec2 angle = {};
	bool needRotation = true;

	SettingEnum autoBlocks;
	int prevSlot = 0;
	static uint8_t* renderItem;
	unsigned long oldProtect = 0;

	float length = 5.f;

	float timer = 20.f;

	bool showBlockCount = false;

	bool render = true;
	Vec3 blockPos = {};
	bool needRender = true;

	bool horizontal = false;
	float horizontalHigh = 0.f;

	bool tryScaffold(Vec3 blockBelow);

public:

	void selectedBlocks();
	int calcBlocksCount();

	Scaffold();
	~Scaffold();

	// Inherited via IModule
	virtual std::string getModuleName() override;
	virtual void onEnable() override;
	virtual void onDisable() override;
	virtual void onTick(GameMode* gm) override;
	virtual void onPreRender() override;
	//virtual void onPlayerTick(C_Player* player) override;
	virtual void onSendPacket(Packet* packet, bool&) override;
	virtual void onGetPickRange() override;
};
