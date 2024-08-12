#pragma once
#include <stdint.h>

#include "../Utils/HMath.h"
#include "Entity.h"
class GameMode{ 
private:
	virtual int destructorGameMode();
public:
	virtual int startDestroyBlock(Vec3i const& pos, unsigned char blockSide, bool& isDestroyedOut);
	virtual int destroyBlock(Vec3i*, unsigned char,bool);
	virtual int continueDestroyBlock(Vec3i const&, unsigned char blockSide, bool& isDestroyedOut);
	virtual int stopDestroyBlock(Vec3i const&);
	virtual int startBuildBlock(Vec3i const&, unsigned char);
	virtual int buildBlock(Vec3i*, unsigned char, bool);
	virtual int continueBuildBlock(Vec3i const&, unsigned char);
	virtual int stopBuildBlock(void);
	virtual int tick(void);

public:
	virtual int getPickRange(int const&, bool);
	virtual int useItem(uintptr_t&);
	virtual int useItemOn(int&, Vec3i const&, unsigned char, Vec3 const&, int const*);
	virtual int interact(Entity&, Vec3 const&);

public:
	virtual int attack(Entity*);

public:
	virtual int releaseUsingItem(void);

public:
	virtual void setTrialMode(bool);
	virtual bool isInTrialMode(void);

private:
	virtual int registerUpsellScreenCallback(int);
public:
	Player* player;
};

