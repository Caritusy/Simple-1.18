#pragma once

#include "IModule.h"
#include <set>
#include "../ModuleManager.h"

class NameTags:public IModule {
public:
	std::set<std::string> nameTags;
	bool displayArmor = true;
	bool displayDistance = true;
	bool underline = false;
	float opacity = 0.7f;
	bool gameName = true;

	NameTags();
	~NameTags();

	bool* ingameNametagSetting = nullptr;
	bool lastSetting = true;
	bool gotPrevSetting = false;

	// Inherited via IModule
	virtual std::string getModuleName() override;
	virtual void onPreRender() override;
	virtual void onDisable() override;
};

