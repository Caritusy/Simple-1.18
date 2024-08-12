#include "Killaura.h"

Killaura::Killaura() :IModule('R', Category::COMBAT, u8"Attacks entities around you automatically. - 自动攻击你附近的敌人") {
	registerBoolSetting("Simulate CPS", &SimulateCPS, SimulateCPS);
	registerFloatSetting("Range", &range, range, 1.f, 20.f);
	registerFloatSetting("FOV", &FOV, FOV, 1.f, 360.f);
	registerIntSetting("Max CPS", &maxCPS, maxCPS, 1, 30);
	registerIntSetting("Min CPS", &minCPS, minCPS, 1, 30);
	registerBoolSetting("rotations", &rotations, rotations);
	registerBoolSetting("Attack Mob", &isMobAura, isMobAura);

}

Killaura::~Killaura()
{
}

std::string Killaura::getModuleName()
{
	return ("Killaura");
}
std::vector<Entity*> targetList = {};
void findEntity(Entity* currentEntity, bool isRegularEntity) {
	static auto killauraMod = moduleMgr->getModule<Killaura>();
	if (killauraMod->isMobAura) {
		if (currentEntity == nullptr)
			return;

		if (currentEntity == Game.getLocalPlayer())
			return;

		if (!currentEntity->isAlive())
			return;

		if (currentEntity->getEntityTypeId() == 307) // NPC
			return;
	}
	else {
		if (!Target::isValidTarget(currentEntity))
			return;
	}
	Vec2 czxPos(currentEntity->getPos()->x, currentEntity->getPos()->z);
	Vec2 lxzPos(Game.getLocalPlayer()->getPos()->x, Game.getLocalPlayer()->getPos()->z);
	constexpr float r = 180.f / PI;
	if (killauraMod->FOV < 360.f) {
		if (abs(Game.getLocalPlayer()->pitch) > 60.f) { //当视角绝对值大于60度时，计算目标中点与准星中点的距离偏移。其他情况仅计算yaw的偏移
			if (abs(Game.getLocalPlayer()->viewAngles.normAngles().sub(Game.getLocalPlayer()->getPos()->CalcAngle(*currentEntity->getPos()).normAngles()).normAngles().magnitude()) > killauraMod->FOV)
				return;
		}else{
			float zxdist = sqrt((lxzPos.x - czxPos.x) * (lxzPos.x - czxPos.x) + (lxzPos.y - czxPos.y) * (lxzPos.y - czxPos.y));
			float asinyew = asin((czxPos.x - lxzPos.x) / zxdist) * r;
			float acosyew = acos((czxPos.y - lxzPos.y) / zxdist) * r;
			float powce;
			if (asinyew > 0.f) {
				if (acosyew > 90.f)  //1
					powce = -180.f + asinyew;
				else  //2
					powce = -asinyew;
			}
			else {
				if (acosyew > 90.f)  //4
					powce = 180.f + asinyew;
				else  //3
					powce = -asinyew;
			}
			float powceH = powce + killauraMod->FOV / 2.f;
			float powceL = powce - killauraMod->FOV / 2.f;
			if (powceH > 180.f) {
				if (!(Game.getLocalPlayer()->yaw >= powceL || Game.getLocalPlayer()->yaw <= powceH - 360.f))
					return;
			}
			else if (powceL < -180.f) {
				if (!(Game.getLocalPlayer()->yaw >= powceL + 360.f || Game.getLocalPlayer()->yaw <= powceH))
					return;
			}
			else if (!(Game.getLocalPlayer()->yaw >= powceL && Game.getLocalPlayer()->yaw <= powceH))
				return;
		}
	
	}
	float dist = (*currentEntity->getPos()).dist(*Game.getLocalPlayer()->getPos());
	if (dist < killauraMod->range) {
		targetList.push_back(currentEntity);
	}
}

void Killaura::onTick(GameMode* gm) {

	targetListEmpty = targetList.empty();
	targetList.clear();
	Game.forEachValidEntity(findEntity);
	INPUT input = { 0 };
	input.type = INPUT_MOUSE;
	if (!targetList.empty()) {
		std::sort(targetList.begin(), targetList.end(), [](const Entity* lhs, const Entity* rhs) {
			Vec3 localPlayerPos = *Game.getLocalPlayer()->getPos();
			Entity* current = const_cast<Entity*>(lhs);
			Entity* other = const_cast<Entity*>(rhs);
			return (*current->getPos()).dist(localPlayerPos) < (*other->getPos()).dist(localPlayerPos);
			});
		if (minCPS > maxCPS)
			minCPS = maxCPS;
		CPS = random(minCPS, maxCPS);
		if (CPSTime.hasTimedElapsed(1000.f / (float)CPS, true)) {
				if (SimulateCPS && Game.canUseMoveKeys()) {
					input.mi.dwFlags = MOUSEEVENTF_LEFTDOWN;
					SendInput(1, &input, sizeof(INPUT));
					//std::this_thread::sleep_for(std::chrono::milliseconds(20));

					input.mi.dwFlags = MOUSEEVENTF_LEFTUP;
					SendInput(1, &input, sizeof(INPUT));
					//std::this_thread::sleep_for(std::chrono::milliseconds(20));

					Game.getLocalPlayer()->swing();
					Game.getGameMode()->attack(targetList[0]);
					/*mouse_event(MOUSEEVENTF_LEFTDOWN, 0, 0, 0, 0);mouse_event(MOUSEEVENTF_LEFTUP, 0, 0, 0, 0);*/
				}
				else {
					Game.getLocalPlayer()->swing();
					Game.getGameMode()->attack(targetList[0]);
				}
			}
			if (rotations) {
				angle = Game.getLocalPlayer()->getPos()->CalcAngle(*targetList[0]->getPos());
			//	Game.getLocalPlayer()->setRot(angle);
			}
		
		
	}
}

void Killaura::onEnable() {
	if (Game.getLocalPlayer() == nullptr)
		setEnabled(false);
	CPSTime.resetTime();
}

void Killaura::onSendPacket(Packet* packet, bool& cancelSend) {
	if (!targetList.empty()) {
		if (packet->isInstanceOf<PlayerAuthInputPacket>(AuthInputPacket)) {
			auto* authInputPacket = reinterpret_cast<PlayerAuthInputPacket*>(packet);
			authInputPacket->pitch = angle.x;
			authInputPacket->yaw = angle.y;
			authInputPacket->InputAD = angle.x;
			authInputPacket->InputWS = angle.y;
		}
	}
}