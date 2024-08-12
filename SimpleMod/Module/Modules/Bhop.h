#pragma once

#include "../ModuleManager.h"
#include "IModule.h"

class Bhop : public IModule {
private:
	float maxSpeed = 0.45f;
	float minSpeed = 0.38f;
	float speed = 0.f;
	bool hive = false;
	float speedFriction = 0.65f;
	float cashedStepHeignt = 0.5f;
public:
	Bhop();
	~Bhop();

	// Inherited via IModule
	virtual std::string getModuleName() override;
	virtual void onMove(C_MoveInputHandler* input) override;
	virtual void onTick(GameMode* mod) override;

	virtual void onEnable() {
		auto player = Game.getLocalPlayer();
		if (player == nullptr) return; else cashedStepHeignt = player->stepHeight;
	};
	virtual void onDisable() {
		auto player = Game.getLocalPlayer();
		if (player == nullptr) return; else player->stepHeight = cashedStepHeignt;
	};
};
