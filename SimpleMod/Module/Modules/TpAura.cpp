#include "TpAura.h"

TpAura::TpAura() : IModule(0, Category::COMBAT, u8"Teleport to target around you. - 将你传送到附近敌人的某处.") {
	registerFloatSetting("Range", &range, range, 1.f, 20.f);
	registerFloatSetting("delay", &delay, delay, 0.f, 1500.f);
}

TpAura::~TpAura(){
}

std::string TpAura::getModuleName(){
return ("TPAura");
}

static std::vector<Entity*> targetList;
void findTarget(Entity* currentEntity, bool isRegularEntity) {
	static auto TPAuraMod = moduleMgr->getModule<TpAura>();

	if (!Target::isValidTarget(currentEntity))
		return;

	float dist = (*currentEntity->getPos()).dist(*Game.getLocalPlayer()->getPos());
	if (dist < TPAuraMod->range) {
		targetList.push_back(currentEntity);
	}
}
void TpAura::onTick(GameMode* gm){
	if (Game.getLocalPlayer() == nullptr || !Game.getLocalPlayer()->isAlive())
		return;
	targetList.clear();
	Game.forEachValidEntity(findTarget);
	if (!targetList.empty() && time.hasTimedElapsed(delay,true)) {
		std::sort(targetList.begin(), targetList.end(), [](const Entity* lhs, const Entity* rhs) {
			Vec3 localPlayerPos = *Game.getLocalPlayer()->getPos();
			Entity* current = const_cast<Entity*>(lhs);
			Entity* other = const_cast<Entity*>(rhs);
			return (*current->getPos()).dist(localPlayerPos) < (*other->getPos()).dist(localPlayerPos);
			});

			Vec3 pos = *targetList[0]->getPos();
			float yaw = targetList[0]->yaw - 180.f;
			pos.x -= sin(yaw * (PI / 180)) * 1.5f;
			pos.y += 1.f;
			pos.z += cos(yaw * (PI / 180)) * 1.5f;
			Game.getLocalPlayer()->setpos(pos);
			Game.getClientInstance()->loopbackPacketSender->sendToServer(&PlayerAuthInputPacket(pos, Game.getLocalPlayer()));
	}
}

void TpAura::onEnable(){
	if (Game.getLocalPlayer() == nullptr)
		this->setEnabled(false);
}
