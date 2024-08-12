#pragma once
#include "IModule.h"
class ClickGuiMod :public IModule{
public:
	ClickGuiMod();
	~ClickGuiMod();

	bool showTooltips = true;

	// Inherited via IModule
	//virtual void onPostRender(MinecraftUIRenderContext* renderCtx) override;
	virtual std::string getModuleName() override;
	virtual void onDisable() override;
	virtual void onEnable() override;
};

