#pragma once
#include "IModule.h"
class AirJump:public IModule
{
public:
	AirJump();
	~AirJump();

	virtual std::string getModuleName() override;
	virtual void onTick(GameMode* gm) override;
};

