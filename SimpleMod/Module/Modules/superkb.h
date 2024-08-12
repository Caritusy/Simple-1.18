#pragma once
#include "IModule.h"
class superkb:public IModule{
private:
	PlayerActionPacket PlayerAction;
	PlayerAuthInputPacket PlayerAuthInput;
	bool packetdist = false;
public:

	superkb();
	~superkb();

	// Inherited via IModule
	virtual std::string getModuleName() override;
	virtual void onAttack(Entity* ent) override;
};

