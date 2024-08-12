#pragma once

#include "../ModuleManager.h"
#include "IModule.h"

class Aimbot : public IModule {
private:
	float range = 4.f;
	bool vertical = true;
	bool sword = false;
	bool click = false;
	float horizontalspeed = 50.f;
	float verticalspeed = 50.f;
	float verticalrange = 40.f;
	float horizontalrange = 60.f;
	bool lock = false;
	std::vector<Entity*> targetList;

public:
	Aimbot();
	~Aimbot();

	// Inherited via IModule
	virtual std::string getModuleName() override;
	virtual void onTick(GameMode* gm) override;
};
