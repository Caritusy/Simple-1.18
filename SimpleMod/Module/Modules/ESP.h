#pragma once

#include "IModule.h"
#include "../ModuleManager.h"

class ESP : public IModule {
public:
	SettingEnum target;
	SettingEnum renderMode;

	bool doRainbow = true;
	ESP();
	~ESP();

	// Inherited via IModule
	virtual std::string getModuleName() override;
	virtual void onPreRender() override;
};
