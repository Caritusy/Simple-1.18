#include "NameTags.h"
#include "../../../Memory/Hooks.h"
NameTags::NameTags() : IModule(0, Category::VISUAL, "Shows better nametags.") {
	registerBoolSetting("Underline", &underline, underline);
	registerBoolSetting("GameName", &gameName, gameName);
	registerBoolSetting("Armor", &displayArmor, displayArmor);
	registerBoolSetting("Distance", &displayDistance, displayDistance);
	registerFloatSetting("Opacity", &opacity, opacity, 0.f, 1.f);
}

NameTags::~NameTags()
{
}

std::string NameTags::getModuleName()
{
	return ("NameTags");
}

void drawNameTags(Entity* ent, bool) {
	static auto nameTagsMod = moduleMgr->getModule<NameTags>();

	if (!ent->checkNameTagFunc())
		return;

	if (ent->GetNameTag()->getTextLength() < 1)
		return;


	if (Target::isValidTarget(ent) && nameTagsMod != nullptr){
		nameTagsMod->nameTags.insert(Utils::sanitize(ent->GetNameTag()->getText()));
		float dist = ent->getPos()->dist(*Game.getLocalPlayer()->getPos());
		DrawUtils::drawNameTags(ent, fmax(0.8f, 3.f / dist));
	}
}
void NameTags::onPreRender(){
	if (Game.getLocalPlayer() == nullptr || !GameData::canUseMoveKeys())
		return;

	Game.forEachValidEntity(drawNameTags);
}

void NameTags::onDisable(){
	if (!gameName) {
		if (*ingameNametagSetting != lastSetting) {
			*ingameNametagSetting = lastSetting;
			gotPrevSetting = false;
		}
	}
}
