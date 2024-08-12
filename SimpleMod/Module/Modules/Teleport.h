#pragma once

#include "IModule.h"

class Teleport : public IModule {
private:
	bool hasClicked = false;
	bool onlyHand = false;
	bool shouldTP = false;
	bool onlySneak = true;
	Vec3 tpPos;
	Vec3 pos;
	SettingEnum mode;
public:
	Teleport();
	~Teleport();

	// Inherited via IModule
	virtual std::string getModuleName() override;
	virtual void onTick(GameMode* gm) override;
};
