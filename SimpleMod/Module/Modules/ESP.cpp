#include "ESP.h"
#include "../../../Memory/Hooks.h"
ESP::ESP() : IModule('O', Category::VISUAL, "Makes it easier to find entities around you.") {
    registerBoolSetting("Rainbow", &doRainbow, doRainbow);
}

ESP::~ESP()
{
}

std::string ESP::getModuleName()
{
	return ("ESP");
}
static float rcolors[4];
void doRenderStuff(Entity* ent, bool isRegularEntitie) {

	static auto espMod = moduleMgr->getModule<ESP>();
	LocalPlayer* localPlayer = Game.getLocalPlayer();
	if (!Target::isValidTarget(ent))
		return;
	if (ent->hurttime > 10 || ent->hurttime < 0)
		ent->hurttime = 0;
	if (espMod->doRainbow)
		DrawUtils::setColor(rcolors[0], rcolors[1], rcolors[2], (float)fmax(0.1f, (float)fmin(1.f, 15 / (ent->hurttime + 1))));
	else
		DrawUtils::setColor(0.9f, 0.9f, 0.9f, (float)fmax(0.1f, (float)fmin(1.f, 15 / (ent->hurttime + 1))));
	//printf("lower[x%f y%f z%f]", Game.getLocalPlayer()->aabb.lower.x, Game.getLocalPlayer()->aabb.lower.y, Game.getLocalPlayer()->aabb.lower.z);
//		printf("lower[x%f y%f z%f]", Game.getLocalPlayer()->aabb.upper.x, Game.getLocalPlayer()->aabb.upper.y, Game.getLocalPlayer()->aabb.upper.z);
	float distance = (*localPlayer->getPos()).dist(*ent->getPos());
	DrawUtils::drawBox(ent->aabb.lower, ent->aabb.upper, (float)fmax(0.2f, 1 / (float)fmax(1, distance)));
	//DrawUtils::fillRectangle({ 0,0 }, { 255,255 });
}
void ESP::onPreRender(){
	if (Game.getLocalPlayer() != nullptr && GameData::canUseMoveKeys()) {
		{
			if (rcolors[3] < 1) {
				rcolors[0] = 0.2f;
				rcolors[1] = 0.2f;
				rcolors[2] = 1.f;
				rcolors[3] = 1;
			}

			Utils::ApplyRainbow(rcolors, 0.0015f);
		}
		Game.forEachValidEntity(doRenderStuff);
	}
}
