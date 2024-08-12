#pragma once

#include "IModule.h"

class NoFriends : public IModule {
public:
	NoFriends();
	~NoFriends();

	// Inherited via IModule
	virtual std::string getModuleName() override;
};
