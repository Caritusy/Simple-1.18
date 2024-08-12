#pragma once
#include "IMCCommand.h"
class PanicCommand:public IMCCommand{
public:
	PanicCommand();
	~PanicCommand();

	// Inherited via IMCCommand
	virtual bool execute(std::vector<std::string>* args) override;
};

