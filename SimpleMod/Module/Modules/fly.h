#pragma once
#include "IModule.h"
class Fly :public IModule {
private:
	float horizontalSpeed = 1.5f;
	float verticalSpeed = 0.5;
	bool elytraSpoof = false;
	Vec3 oldOffset = {};
	PlayerActionPacket PlayerAction;
public:
	Fly();
	~Fly();

	virtual void onEnable() override;
	virtual std::string getModuleName() override;
	virtual void onTick(GameMode* gm) override;
	virtual void onDisable() override;
	virtual void onMove(C_MoveInputHandler* input) override;
	virtual void onSendPacket(Packet* packet, bool& cancelSend) override;
};

