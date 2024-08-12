#pragma once
#include "IMCCommand.h"
class SpammerCommand:public IMCCommand
{public:
	SpammerCommand();
	~SpammerCommand();

	virtual bool execute(std::vector<std::string>* args) override;
};

