#include "fly.h"
Fly::Fly():IModule('F', Category::MOVEMENT, "Fly to the sky"){
	registerFloatSetting("Horizontal Speed", &horizontalSpeed, horizontalSpeed, 0.1f, 10.f);
	registerFloatSetting("Vertical Speed", &verticalSpeed, verticalSpeed, 0.1f, 10.f);
	registerBoolSetting("Elytra Spoof", &elytraSpoof, elytraSpoof);
}

Fly::~Fly()
{
}

void Fly::onEnable(){
	if (Game.getLocalPlayer() == nullptr)
		return;
	if (elytraSpoof) {
		PlayerActionPacket actionPacket;
		actionPacket.action = 15;  //开启鞘翅
		actionPacket.entityRuntimeId = Game.getLocalPlayer()->EntityRuntimeid;
		Game.getClientInstance()->loopbackPacketSender->sendToServer(&actionPacket);
	}
	oldOffset = Game.getLocalPlayer()->aabb.upper.sub(Game.getLocalPlayer()->aabb.lower);
}

std::string Fly::getModuleName(){
	return "Fly";
}

void Fly::onTick(GameMode* gm){	
	if (Game.getLocalPlayer() == nullptr)
		return;
	Game.getLocalPlayer()->canFly = true;
	Game.getLocalPlayer()->fallDistance = 0.f;
	Game.getLocalPlayer()->velocity = Vec3(0, 0, 0);
	Game.getLocalPlayer()->aabb.upper.y = Game.getLocalPlayer()->aabb.lower.y - 1.8f;
}

void Fly::onDisable(){
	if (Game.getLocalPlayer() == nullptr)
		return;
	if (Game.getLocalPlayer()->gamemode != 1)
		Game.getLocalPlayer()->canFly = false;
	Game.getLocalPlayer()->aabb.upper = Game.getLocalPlayer()->aabb.lower.add(oldOffset);
}

void Fly::onMove(C_MoveInputHandler* input){
	LocalPlayer* localPlayer = Game.getLocalPlayer();
	if (localPlayer == nullptr)
		return;
	Vec3 localPlayerPos = *localPlayer->getPos();
	float yaw = localPlayer->yaw;
	Vec2 moveVec2d = { input->forwardMovement, -input->sideMovement };
	bool pressed = moveVec2d.magnitude() > 0.01f;

	if (GameData::isKeyDown(0x20) && GameData::canUseMoveKeys()) {
		localPlayer->velocity.y += verticalSpeed;
		localPlayer->fallDistance = 0.f;
	}
	if (input->isSneakDown) {
		localPlayer->velocity.y -= verticalSpeed;
		localPlayer->fallDistance = 0.f;
	}
	if (GameData::isKeyDown('D') && GameData::canUseMoveKeys()) {
		yaw += 90.f;
		if (GameData::isKeyDown('W') && GameData::canUseMoveKeys())
			yaw -= 45.f;
		else if (GameData::isKeyDown('S') && GameData::canUseMoveKeys())
			yaw += 45.f;
	}
	if (GameData::isKeyDown('A') && GameData::canUseMoveKeys()) {
		yaw -= 90.f;
		if (GameData::isKeyDown('W') && GameData::canUseMoveKeys())
			yaw += 45.f;
		else if (GameData::isKeyDown('S') && GameData::canUseMoveKeys())
			yaw -= 45.f;
	}
	if (GameData::isKeyDown('S') && GameData::canUseMoveKeys() && !GameData::isKeyDown('A') && GameData::canUseMoveKeys() && !GameData::isKeyDown('D') && GameData::canUseMoveKeys())
		yaw += 180.f;

	if (pressed) {
		float calcYaw = (yaw + 90.f) * (PI / 180.f);
		Vec3 moveVec;
		moveVec.x = cos(calcYaw) * horizontalSpeed;
		moveVec.y = localPlayer->velocity.y;
		moveVec.z = sin(calcYaw) * horizontalSpeed;
		localPlayer->lerpMotion(moveVec);
	}
}

void Fly::onSendPacket(Packet* packet, bool& cancelSend){
	if (packet->isInstanceOf<PlayerActionPacket>(PlayerAction)) {
		PlayerActionPacket* packets = reinterpret_cast<PlayerActionPacket*>(packet);
		if (elytraSpoof) {
			if (packets->action == 16) { //客户端自动发送的关闭鞘翅包
				cancelSend = true; //取消发送这个包
			}
		}
	}

}
