#pragma once
#include "IModule.h"
class NoPacket:public IModule{
public:
	NoPacket();
	~NoPacket();
	
	virtual std::string getModuleName() override;
};

