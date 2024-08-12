#include "NoWeb.h"

NoWeb::NoWeb():IModule('0',Category::MOVEMENT, u8"Ignore cobwebs slowdown. - 你可以无视蜘蛛网的减速.")
{
}

NoWeb::~NoWeb()
{
}

std::string NoWeb::getModuleName(){
	return ("NoWeb");
}

void NoWeb::onTick(GameMode* gm){
	Game.getLocalPlayer()->slowdownFactor = { 0,0,0 };
}
