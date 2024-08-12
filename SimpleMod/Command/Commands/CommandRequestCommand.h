#pragma once
#include "IMCCommand.h"
class CommandRequestCommand:public IMCCommand{
public:
	CommandRequestCommand();
	~CommandRequestCommand();

	virtual bool execute(std::vector<std::string>* args) override;
};

