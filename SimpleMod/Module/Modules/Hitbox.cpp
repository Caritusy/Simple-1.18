#include "Hitbox.h"
Hitbox::Hitbox() : IModule(0, Category::COMBAT, "Increase an entitys hitbox size.") {
	registerFloatSetting("Height", &height, height, 1.7f, 10.f);
	registerFloatSetting("Width", &width, width, 0.6f, 10.f);
}

Hitbox::~Hitbox()
{
}

std::string Hitbox::getModuleName(){
	return ("Hitbox");
}
void EnableHitbox(Entity* currentEntity, bool isRegularEntitie) {
	static auto hitboxMod = moduleMgr->getModule<Hitbox>();

	if (!Target::isValidTarget(currentEntity))
		return;

	float dist = (*currentEntity->getPos()).dist(*Game.getLocalPlayer()->getPos());

	if (dist < 20.f) {
		currentEntity->width = hitboxMod->width;
		currentEntity->height = hitboxMod->height;
	}
}
void DisableHitbox(Entity* currentEntity, bool isRegularEntitie) {
	currentEntity->width = 0.6;
	currentEntity->height = 1.8;
}

void Hitbox::onTick(GameMode* gm){
	if (Game.getLocalPlayer() == nullptr)
		return;

	Game.forEachEntity(EnableHitbox);
}

void Hitbox::onDisable()
{
}
