#include "InfiniteAura.h"

InfiniteAura::InfiniteAura() : IModule('P', Category::COMBAT, "Killaura but with infinite reach.") {
	registerFloatSetting("TPDistance", &tpDistance, tpDistance, 1.f, 20.f);
	registerFloatSetting("Range", &range, range, 15.f, 128.f);
	registerIntSetting("CPS", &CPS, CPS, 1, 20);
	registerBoolSetting("RenderPos", &renderPos, renderPos);
}

InfiniteAura::~InfiniteAura()
{
}

std::string InfiniteAura::getModuleName() {
	return ("InfiniteAura");
}
void findEntities(Entity* currentEntity, bool isRegularEntitie) {
	static auto infiniteAuraMod = moduleMgr->getModule<InfiniteAura>();

	if (!Target::isValidTarget(currentEntity))
		return;

	float dist = (*currentEntity->getPos()).dist(*Game.getLocalPlayer()->getPos());

	if (dist < infiniteAuraMod->range) {
		infiniteAuraMod->targetList.push_back(currentEntity);
	}
}
void InfiniteAura::onTick(GameMode* gm)
{
	static int tick = 0;
	targetList.clear();

	Game.forEachValidEntity(findEntities);
	++tick;
	if (tick >= 10) {
		tick = 0;
	}
	else if (tick == 1) {
		if (!targetList.empty() && CPSTime.hasTimedElapsed(1000.f / (float)CPS, true)) {
			LocalPlayer* localPlayer = Game.getLocalPlayer();

			posList.clear();

			std::sort(targetList.begin(), targetList.end(), [](const Entity* lhs, const Entity* rhs) {
				Vec3 localPlayerPos = *Game.getLocalPlayer()->getPos();
				Entity* current = const_cast<Entity*>(lhs);
				Entity* other = const_cast<Entity*>(rhs);
				return (*current->getPos()).dist(localPlayerPos) < (*other->getPos()).dist(localPlayerPos);
				});
			float calcYaw = (localPlayer->yaw + 90) * (PI / 180);
			float calcPitch = (localPlayer->pitch) * -(PI / 180);

			float teleportX = cos(calcYaw) * cos(calcPitch) * 3.f;
			float teleportZ = sin(calcYaw) * cos(calcPitch) * 3.f;

			Vec3 localPlayerPos = *localPlayer->getPos();
			for (auto target : targetList) {
				Vec3 targetPos = *target->getPos();

				Vec3 tpPos = Vec3(targetPos.x - teleportX, targetPos.y, targetPos.z - teleportZ);

				int times = ceil(localPlayerPos.dist(tpPos) / tpDistance); //需要传送的次数

				for (int n = 1; n <= times; n++) {
					Vec3 pos = localPlayerPos.add(tpPos.sub(localPlayerPos).div(times).mul(n));
					Game.getClientInstance()->loopbackPacketSender->sendToServer(&PlayerAuthInputPacket(pos, localPlayer));

					posList.push_back(pos);
				}

				localPlayer->swing();
				Game.getGameMode()->attack(target);
				static int delay = 0;
				//回来
			//	delay++;
				localPlayerPos = *localPlayer->getPos();
				//	if (delay >= 20) {
				for (int n = 1; n <= times; n++) {
					Vec3 pos = tpPos.add(localPlayerPos.sub(tpPos).div(times).mul(n));
					Game.getClientInstance()->loopbackPacketSender->sendToServer(&PlayerAuthInputPacket(pos, localPlayer));
				}
				//		delay = 0;
				//	}

				if (mode.selected == 0) {
					break;
				} //Single
			}
		}
	}

}

void InfiniteAura::onEnable(){
	if (Game.getLocalPlayer() == nullptr) {
		this->setEnabled(false);
	}
	posList.clear();
	CPSTime.resetTime();
}

void InfiniteAura::onSendPacket(Packet* packet, bool& cancelSend){
	
}
