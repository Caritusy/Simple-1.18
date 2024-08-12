#include "CPSboost.h"

CPSboost::CPSboost():IModule(0x0,Category::COMBAT,"Attack the target continuously."){
	registerIntSetting("CPS", &CPS, CPS, 2, 114514);
}

CPSboost::~CPSboost(){
}

std::string CPSboost::getModuleName()
{
	return "CPSboost";
}
static bool i = false;
void attack(Entity* ent) {
	static auto CPSboostmod = moduleMgr->getModule<CPSboost>();
	int e = 0;
	for (e = 0;e < CPSboostmod->CPS;e++) {
		Game.getGameMode()->attack(ent);
	}
	if (e >= CPSboostmod->CPS) i = false;
}
void CPSboost::onAttack(Entity* ent){
	if (!i) {
		i = true;
		attack(ent);
	}
}
