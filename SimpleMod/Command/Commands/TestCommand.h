#pragma once
#include "IMCCommand.h"
class TestCommand:public IMCCommand{
public:
	TestCommand();
	~TestCommand();

	// Inherited via IMCCommand
	virtual bool execute(std::vector<std::string>* args) override;
};

