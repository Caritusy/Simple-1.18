#pragma once

#include "IModule.h"

class FullBright : public IModule {
public:
	float intensity = 25.f;
	float* gammaPtr = nullptr;
	FullBright();
	~FullBright();

	// Inherited via IModule
	virtual std::string getModuleName() override;
	virtual void onTick(GameMode* gm) override;
	virtual void onEnable() override;
	virtual void onDisable() override;
};
