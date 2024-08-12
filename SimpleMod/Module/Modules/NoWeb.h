#pragma once
#include "IModule.h"
class NoWeb:public IModule{
public:
	NoWeb();
	~NoWeb();

	virtual std::string getModuleName() override;
	virtual void onTick(GameMode* gm) override;
};

