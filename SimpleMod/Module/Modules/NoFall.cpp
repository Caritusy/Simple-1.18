#include "NoFall.h"

NoFall::NoFall() : IModule(VK_NUMPAD3, Category::PLAYER, "Prevents you from taking falldamage") {
}

NoFall::~NoFall()
{
}

std::string NoFall::getModuleName()
{
	return ("NoFall");
}

void NoFall::onSendPacket(Packet* packet, bool& cancelSend) {
	//if (packet->isInstanceOf<PlayerAuthInputPacket>(PlayerAuthInput)) {
	//	auto* authInputPacket = reinterpret_cast<PlayerAuthInputPacket*>(packet);
	//	authInputPacket->pos = *Game.getLocalPlayer()->getPos();
	//	authInputPacket->onGround = true;
	//}
}

void NoFall::onTick(GameMode* gm) {
	PlayerAction.action = 7;
	PlayerAction.entityRuntimeId = Game.getLocalPlayer()->EntityRuntimeid;
	Game.getClientInstance()->loopbackPacketSender->sendToServer(&PlayerAction);
}