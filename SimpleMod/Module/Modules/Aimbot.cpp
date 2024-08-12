#include "Aimbot.h"

Aimbot::Aimbot() : IModule(0, Category::COMBAT, "Automatically aims at the nearest entity.") {
	registerFloatSetting("Range", &range, range, 3.f, 8.f);
	registerFloatSetting("Horizontal Speed", &horizontalspeed, horizontalspeed, 30.f, 99.f);
	registerFloatSetting("Vertical Speed", &verticalspeed, verticalspeed, 30.f, 99.f);
	registerFloatSetting("Horizontal Range", &horizontalrange, horizontalrange, 20.f, 180.f);
	registerFloatSetting("Vertical Range", &verticalrange, verticalrange, 20.f, 180.f);
	registerBoolSetting("Vertical", &vertical, vertical);
	registerBoolSetting("Require Click", &click, click);
	registerBoolSetting("Only Weapon", &sword, sword);
	registerBoolSetting("Aimlock", &lock, lock);
}

Aimbot::~Aimbot()
{
}

std::string Aimbot::getModuleName()
{
	return ("Aimbot");
}
struct CompareTargetEnArray {
	bool operator()(Entity* lhs, Entity* rhs) {
		LocalPlayer* localPlayer = Game.getLocalPlayer();
		return (*lhs->getPos()).dist(*localPlayer->getPos()) < (*rhs->getPos()).dist(*localPlayer->getPos());
	}
};
void Aimbot::onTick(GameMode* gm){
	LocalPlayer* localPlayer = Game.getLocalPlayer();
	if (!localPlayer || !GameData::canUseMoveKeys())
		return;
	std::vector<Entity*> allEntities;
	Game.forEachEntity([&](Entity* e, bool) -> void {
		allEntities.push_back(e);
		});
	targetList.clear();
	for (size_t i = 0; i < allEntities.size(); i++) {
		Entity* currentEntity = allEntities.at(i);

		if (!Target::isValidTarget(currentEntity))
			return;

		float dist = (*currentEntity->getPos()).dist(*Game.getLocalPlayer()->getPos());

		if (dist < range)
			targetList.push_back(currentEntity);
	}
	if (targetList.size() > 0) {
		std::sort(targetList.begin(), targetList.end(), CompareTargetEnArray());
		Vec3 origin = Game.getClientInstance()->levelRenderer->getOrigin();

		Vec2 angle = origin.CalcAngle(*targetList[0]->getPos());
		Vec2 appl = angle.sub(localPlayer->viewAngles).normAngles();
		appl.x = -appl.x;
		if ((appl.x < verticalrange && appl.x > -verticalrange) && (appl.y < horizontalrange && appl.y > -horizontalrange)) {
			if (!lock) {
				appl.x /= (100.f - verticalspeed);
				appl.y /= (100.f - horizontalspeed);
				if (appl.x >= 1 || appl.x <= -1) appl.div(abs(appl.x));
				if (appl.y >= 1 || appl.y <= -1) appl.div(abs(appl.y));
			}
			if (!vertical)
				appl.x = 0;
		//	localPlayer->applyTurnDelta(&appl);
		}
	}
}
