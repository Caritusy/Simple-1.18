#pragma once

#include "IModule.h"

class BlockReach : public IModule {
private:
	float blockReach = 7.f;

public:
	BlockReach();
	~BlockReach();

	inline float getBlockReach() { return blockReach; };
	inline void setBlockReach(float reach) { blockReach = reach; };
	// Inherited via IModule
	virtual std::string getModuleName() override;
};
