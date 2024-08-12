#include "Freecam.h"

Freecam::Freecam() : IModule('V', Category::MISC, "Move your camera without moving the player.") {
	registerFloatSetting("Speed", &speed, speed, 0.50f, 1.25f);
}

Freecam::~Freecam()
{
}

std::string Freecam::getModuleName()
{
	return ("Freecam");
}

void Freecam::onTick(GameMode* gm){
	Game.getLocalPlayer()->fallDistance = 0.f;
	Game.getLocalPlayer()->velocity = Vec3(0, 0, 0);
	Game.getLocalPlayer()->aabb.upper.y = Game.getLocalPlayer()->aabb.lower.y - 1.8f;
}

void Freecam::onMove(C_MoveInputHandler* input){
	auto player = Game.getLocalPlayer();
	if (player == nullptr)
		return;
	Vec3 moveVec2d = { input->forwardMovement, -input->sideMovement };
	bool pressed = moveVec2d.magnitude() > 0.01f;

	float calcYaw = (player->yaw + 90) * (PI / 180);
	Vec3 moveVec;
	float c = cos(calcYaw);
	float s = sin(calcYaw);
	moveVec2d = { moveVec2d.x * c - moveVec2d.y * s, moveVec2d.x * s + moveVec2d.y * c };
	moveVec.x = moveVec2d.x * speed;
	moveVec.y = player->velocity.y;
	moveVec.z = moveVec2d.y * speed;
	if (pressed)
		player->lerpMotion(moveVec);
	//C_MovePlayerPacket p(g_Data.getLocalPlayer(), *g_Data.getLocalPlayer()->getPos());
	if (GameData::isKeyDown(0x20)&& GameData::canUseMoveKeys()) {
		player->velocity.y += 0.50f;
	}
	if (input->isSneakDown) {
		player->velocity.y -= 0.50f;
	}
}

void Freecam::onEnable(){
	auto localPlayer = Game.getLocalPlayer();
	if (localPlayer != nullptr) {
		oldPos = *localPlayer->getPos();
		oldOffset = localPlayer->aabb.upper.sub(localPlayer->aabb.lower);

		pos = oldPos;
		pitch = localPlayer->pitch;
		yaw = localPlayer->yaw;
	}
}

void Freecam::onDisable(){
	auto plr = Game.getLocalPlayer();
	if (plr) {
		plr->setpos(oldPos);
		plr->aabb.upper = plr->aabb.lower.add(oldOffset);
	}
}

void Freecam::onSendPacket(Packet* packet, bool& cancelSend){
	if (packet->isInstanceOf<PlayerActionPacket>(PlayerAction)) {
		PlayerActionPacket* packets = reinterpret_cast<PlayerActionPacket*>(packet);
		if (packets->action == 9) { //²»·¢ËÍ¼²ÅÜ°ü
			cancelSend = true;
		}
	}
	else if (packet->isInstanceOf<C_MovePlayerPacket>(Move)) {
		cancelSend = true;
	}
	else if (packet->isInstanceOf<PlayerAuthInputPacket>(PlayerAuthInput)) {
		PlayerAuthInputPacket* packets = reinterpret_cast<PlayerAuthInputPacket*>(packet);
		packets->pos = pos;
		packets->pitch = pitch;
		packets->yaw = yaw;
		packets->yawUnused = yaw;
		packets->Velocity = velocity;
	}
}
