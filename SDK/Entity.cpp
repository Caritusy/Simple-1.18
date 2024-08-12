#include "Entity.h"

Entity* Level::getEntity(){
	Entity* retval = nullptr;
	//Game.forEachEntity([this, &retval](Entity* ent, bool b) {
	//	if (*(__int64*)((__int64)ent + 0x10) == GamingEntityFinder) {
	//		retval = ent;
	//		return;
	//	}
	//	});
	return retval;
}

float Entity::getBlocksPerSecond()
{
	return getBlocksPerTick() * 20.f;
}

bool Entity::checkNameTagFunc(){
	__try {
		return this->GetNameTag() != nullptr;
	}
	__except (EXCEPTION_EXECUTE_HANDLER) {
		return false;
	}
}

C_PlayerInventoryProxy* Player::getSupplies()
{
	return *reinterpret_cast<C_PlayerInventoryProxy**>(reinterpret_cast<__int32>(this) + 0xD2C);
}
