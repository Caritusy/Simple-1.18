#pragma once

#include "IModule.h"

class Freecam : public IModule {
private:
	Vec3 oldPos;
	Vec3 oldOffset = {};
	float speed = 0.325f;

	Vec3 pos;

	Vec3 velocity = Vec3(0.f, 0.f, 0.f);

	PlayerActionPacket PlayerAction;
	C_MovePlayerPacket Move;
	PlayerAuthInputPacket PlayerAuthInput;
public:
	float pitch;
	float yaw;
	Freecam();
	~Freecam();

	// Inherited via IModule
	virtual std::string getModuleName() override;
	virtual void onTick(GameMode* gm) override;
	virtual void onMove(C_MoveInputHandler* input) override;
	virtual void onEnable() override;
	virtual void onDisable() override;
	virtual void onSendPacket(Packet* packet, bool& cancelSend) override;
};
