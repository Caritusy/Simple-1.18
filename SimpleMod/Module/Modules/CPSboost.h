#pragma once
#include "IModule.h"
#include "../ModuleManager.h"
class CPSboost:public IModule{
private:

	TimerUtil CPSTime;
public:

	int CPS = 800;

	CPSboost();
	~CPSboost();

	virtual std::string getModuleName() override;
	virtual void onAttack(Entity* ent) override;
};

