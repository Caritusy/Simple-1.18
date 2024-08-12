#include "Scaffold.h"
#include <array>
#include "../SimpleMod/DrawUtils.h"
Scaffold::Scaffold() : IModule('G', Category::WORLD, "Automatically build blocks beneath you.") {
		registerFloatSetting("Extend Length", &length, length, 0.f, 10.f);
		registerFloatSetting("Timer", &timer, timer, 20.f, 40.f);
		registerBoolSetting("Horizontal", &horizontal, horizontal);
		registerBoolSetting("BlocksCount", &showBlockCount, showBlockCount);
		registerBoolSetting("RenderBlocks", &render, render);
}

Scaffold::~Scaffold(){

}

std::string Scaffold::getModuleName(){
	return "Scaffold";
}

void Scaffold::onEnable(){
	if (Game.getLocalPlayer() == nullptr)
		return;

	horizontalHigh = Game.getLocalPlayer()->getPos()->y;
	horizontalHigh -= Game.getLocalPlayer()->height;
	horizontalHigh -= 0.5f;
	prevSlot = Game.getLocalPlayer()->getSupplies()->selectedHotbarSlot;

	needRotation = false;
	needRender = false;
}

void Scaffold::onDisable() {

	if (Game.getLocalPlayer() != nullptr) {
		Game.getLocalPlayer()->getSupplies()->selectedHotbarSlot = prevSlot;
	}
}


void Scaffold::onTick(GameMode* gm)
{
	if (Game.getLocalPlayer() == nullptr)
		return;


	//	if (rotations.selected == 3) { //The Hive
			Vec3 blockBelow = *Game.getLocalPlayer()->getPos();
			blockBelow.y -= Game.getLocalPlayer()->height;
			blockBelow.y -= 0.8f;

			float cal = (Game.getLocalPlayer()->yaw + 90) * (PI / 180);
			blockBelow.x += cos(cal) * 1;
			blockBelow.z += sin(cal) * 1;

			Vec3 vel = Game.getLocalPlayer()->velocity.normalize();
			blockBelow.x -= vel.x * 0.4f;
			blockBelow.z -= vel.x * 0.4f;

			angle = Game.getLocalPlayer()->getPos()->CalcAngle(blockBelow);
	//	}

		if (Game.getLocalPlayer()->getBlocksPerSecond() > 0.1f) {
			Game.getLocalPlayer()->pitch = angle.x;
			Game.getLocalPlayer()->bodyYaw = angle.y;
			Game.getLocalPlayer()->yawUnused1 = angle.y;
			Game.getLocalPlayer()->bodyYaw = angle.y;
		//	Game.getLocalPlayer()->setRot(angle);
		}
	
}
void Scaffold::onPreRender()
{
	if (Game.canUseMoveKeys()) {
		//if (showBlockCount) {
		//	Vec2 windowSize = Game.getClientInstance()->getGuiData()->windowSize;
		//	std::string countText = "Blocks:" + std::to_string(calcBlocksCount());
		//	DrawUtils::drawText(Vec2{ windowSize.x / 2.f, windowSize.y / 2.f + 20.f }, &countText, (255, 255, 255), 1.3f);
		//	// vec4_t renderPos = {};
		//	// DrawUtils::fillRectangle(renderPos, MC_Color(13, 29, 48), 1.f);
		//}

		if (render && needRender) {
			DrawUtils::setColor(0.f, 0.3705f, 1.f, 1.f);
			DrawUtils::drawBox(blockPos, blockPos.add(1), 0.5f, false);
		}
	}
}
bool Scaffold::tryScaffold(Vec3 blockBelow){
	blockBelow = blockBelow.floor();

	blockPos = blockBelow;
	needRender = true;

	LocalPlayer* localPlayer = Game.getLocalPlayer();
		Vec3i block(blockBelow);

		//寻找周围可以放置的方块
		static std::array<Vec3i, 6> checklist = {
			Vec3i(0, -1, 0), //0
			Vec3i(0, 1, 0), //1
			Vec3i(0, 0, -1), //2
			Vec3i(0, 0, 1), //3
			Vec3i(-1, 0, 0), //4
			Vec3i(1, 0, 0) //5
		};
		bool foundCandidate = false;
		int blockFace = 0;
		for (auto current : checklist) {
			Vec3i calc = block.sub(current);
			//if (!(localPlayer->region->getBlock(calc))) {
			//	//寻找固体方块点击
			//	foundCandidate = true;
			//
			//	break;
			//}
			block = calc;
			blockFace++;
		}
		if (foundCandidate) {
			Vec3* localPos = localPlayer->getPos();
		}
		Game.getGameMode()->buildBlock(&block, blockFace, true);
	
	return true;
}

void Scaffold::selectedBlocks()
{
}

int Scaffold::calcBlocksCount()
{
	return 0;
}
void Scaffold::onSendPacket(Packet* packet, bool&){
	if (needRotation) {
		if (Game.getLocalPlayer()->getBlocksPerSecond() > 0.1f) {
			if (packet->isInstanceOf<PlayerAuthInputPacket>(PlayerAuthInput)) {
				PlayerAuthInputPacket* authInputPacket = reinterpret_cast<PlayerAuthInputPacket*>(packet);
				//authInputPacket->pitch = angle.x;
				authInputPacket->pitch = 89;
				authInputPacket->yawUnused = angle.y;
				authInputPacket->yaw = angle.y;
			}
		}
	}
}

void Scaffold::onGetPickRange(){
	LocalPlayer* localPlayer = Game.getLocalPlayer();
	if (localPlayer == nullptr)
		return;

	if (calcBlocksCount() == 0)
		return;

	float speed = localPlayer->velocity.magnitudexz(); //水平速度
	float bps = localPlayer->getBlocksPerSecond();
	Vec3 velocity = localPlayer->velocity.normalize();

	Vec3 blockBelow = *localPlayer->getPos();
	if (horizontal) {
		blockBelow.y = horizontalHigh;
	}
	else {
		blockBelow.y -= localPlayer->height;
		blockBelow.y -= 0.5f;
	}
	C_Inventory* inv = Game.getLocalPlayer()->getSupplies()->inventory;
	
		if (speed > 0.01f) {  // Are we actually walking?
			blockBelow.z -= velocity.z * 0.5f;
			//if (!tryScaffold(blockBelow)) {
				blockBelow.x -= velocity.x * 0.5f;
				tryScaffold(blockBelow);
				/*if (!tryScaffold(blockBelow) && g_Data.getLocalPlayer()->isSprinting()) {
					blockBelow.z += velocity.z;
					blockBelow.x += velocity.x;
				}*/
			//}
		}
	
}
