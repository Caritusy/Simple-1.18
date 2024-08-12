#include "Bhop.h"

Bhop::Bhop() : IModule(0, Category::MOVEMENT, "Hop around like a bunny!") {
	registerFloatSetting("MaxSpeed", &maxSpeed, maxSpeed, 0.1f, 1.f);
	registerFloatSetting("MinSpeed", &minSpeed, minSpeed, 0.1f, 1.f);
	registerBoolSetting("Hive", &hive, hive);
}

Bhop::~Bhop()
{
}

std::string Bhop::getModuleName(){
	return ("Bhop");
}

void Bhop::onMove(C_MoveInputHandler* input){
	auto player = Game.getLocalPlayer();
	if (player == nullptr) return;

	if (player->isInLava() == 1 || player->isInWater() == 1)
		return;
	if (input->isSneakDown)
		return;
	static auto flyMod = moduleMgr->getModule<Fly>();
	if (flyMod->isEnabled())
		return;

	Vec2 moveVec2d = { input->forwardMovement, -input->sideMovement };
	bool pressed = moveVec2d.magnitude() > 0.01f;
	float calcYaw = (player->yaw + 90) * (PI / 180);
	float c = cos(calcYaw);
	float s = sin(calcYaw);
	moveVec2d = { moveVec2d.x * c - moveVec2d.y * s, moveVec2d.x * s + moveVec2d.y * c };

	Vec3 moveVec;
	if (hive) {
		player->stepHeight = 0.f;
		static bool useVelocity = false;
		if (0.4000000059604645 >= 0.385) {
			if (player->onGround && pressed) player->JumpFromGround();
			useVelocity = false;
		}
		else
			useVelocity = true;

		speedFriction *= 0.9535499811172485;
		if (pressed) {
			player->setSprinting(true);
			if (player->onGround) {
				if (useVelocity && !input->isJumping) player->velocity.y = 0.4000000059604645;
				speedFriction = RandomFloat(0.4190652072429657, 0.48381298780441284);
			}
			else {
				moveVec.x = moveVec2d.x * speedFriction;
				moveVec.y = player->velocity.y;
				moveVec.z = moveVec2d.y * speedFriction;
				player->lerpMotion(moveVec);
			}
		}
	}
	else {
		if (player->onGround && pressed)
			player->JumpFromGround();
		moveVec.x = moveVec2d.x * speed;
		moveVec.y = player->velocity.y;
		moveVec.z = moveVec2d.y * speed;
		if (pressed) player->lerpMotion(moveVec);
	}
}

void Bhop::onTick(GameMode* mod){
	LocalPlayer* localPlayer = Game.getLocalPlayer();
	if (maxSpeed < minSpeed)
		minSpeed = maxSpeed;
	speed = RandomFloat(maxSpeed, minSpeed);
}
