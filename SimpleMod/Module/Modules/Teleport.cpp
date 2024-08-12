#include "Teleport.h"

Teleport::Teleport() : IModule(0, Category::MISC, "Click a block to teleport to it.") {
    registerBoolSetting("Only Hand", &onlyHand, onlyHand);
    registerBoolSetting("Only Sneak", &onlySneak, onlySneak);
}

Teleport::~Teleport()
{
}

std::string Teleport::getModuleName()
{
    return "Teleport";
}

void Teleport::onTick(GameMode* gm){
    if (!GameData::canUseMoveKeys())
        return;
    LocalPlayer* localPlayer = Game.getLocalPlayer();

    Vec3 localPlayerPos = *localPlayer->getPos();

    Level* level = localPlayer->getlevel();
}
