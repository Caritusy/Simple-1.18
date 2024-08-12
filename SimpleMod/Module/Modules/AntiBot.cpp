#include "AntiBot.h"

AntiBot::AntiBot() : IModule(0, Category::PLAYER, "Enable this module to filter out bots!") {
	registerBoolSetting("Hitbox Check", &hitboxCheck, hitboxCheck);
	registerBoolSetting("Name Check", &nameCheck, nameCheck);
	//registerBoolSetting("Invisible Check", &invisibleCheck, invisibleCheck);
	registerBoolSetting("EntityID Check", &entityIdCheck, entityIdCheck);
	//registerBoolSetting("Move Check", &moveCheck, moveCheck);
	registerBoolSetting("GameMode Check", &modeCheck, modeCheck);
	registerBoolSetting("Server bots", &Serverbots, Serverbots);
}

AntiBot::~AntiBot()
{
}

std::string AntiBot::getModuleName()
{
    return "AntiBot";
}
