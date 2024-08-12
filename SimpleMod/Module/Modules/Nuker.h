#pragma once
#include "IModule.h"
class Nuker:public IModule{
private:
	int delay = 0;
	int nukerRadius = 7;
	bool veinMiner = false;
	bool autodestroy = false;
	Vec3i tempPos = *Game.getLocalPlayer()->getPos();
public:
	Nuker();
	~Nuker();

	inline bool isAutoMode() { return autodestroy; };
	int getNukerRadius() { return nukerRadius; };
	inline bool isVeinMiner() { return veinMiner; };

	// Inherited via IModule
	virtual std::string getModuleName() override;
	virtual void onTick(GameMode* gm) override;
};

