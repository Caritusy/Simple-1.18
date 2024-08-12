#pragma once

#include "../ModuleManager.h"
#include "IModule.h"

class Hitbox : public IModule {
public:
	float height = 2.f;
	float width = 4.f;

	Hitbox();
	~Hitbox();

	// Inherited via IModule
	virtual std::string getModuleName() override;
	virtual void onTick(GameMode* gm) override;
	virtual void onDisable() override;
};
