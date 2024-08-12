#pragma once

#include "IModule.h"

class AutoSprint : public IModule {
private:
	bool alldirections = true;

public:
	AutoSprint();
	~AutoSprint();

	// Inherited via IModule
	//virtual void onTick(GameMode* gm) override;
	virtual void onMove(C_MoveInputHandler* input) override;
	virtual std::string getModuleName() override;
};
