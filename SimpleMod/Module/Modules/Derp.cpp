#include "Derp.h"

Derp::Derp() : IModule(0, Category::MISC, "lol you stupid.") {
	registerFloatSetting("Delay", &delay, delay, 0, 6500.f);
	registerBoolSetting("epicStroke",&epicStroke, epicStroke);
	registerBoolSetting("posture",&epicsquat, epicsquat);
}

Derp::~Derp()
{
}

void Derp::onTick(GameMode* gm) {
	//LocalPlayer* player = Game.getLocalPlayer();
	//PlayerAuthInputPacket PlayerAuthInput(*Game.getLocalPlayer()->getPos(),Game.getLocalPlayer());
	//if (epicStroke) {
	//	PlayerAuthInput.pitch = (float)(rand() % 360);
	//	PlayerAuthInput.yaw = (float)(rand() % 360);
	////	PlayerAuthInput.yawUnused= (float)(rand() % 360);
	//}
	////else {
	////	PlayerAuthInput.pitch = (float)(counter % 360);
	////	PlayerAuthInput.yaw = (float)(counter % 360);
	//////	PlayerAuthInput.yawUnused = (float)(counter % 360);
	////}
	//Game.getClientInstance()->loopbackPacketSender->sendToServer(&PlayerAuthInput);
}

std::string Derp::getModuleName() {
	return "Derp";
}

void Derp::onSendPacket(Packet* packet, bool& cancelSend){
	if (delayTime.hasTimedElapsed(delay, true)) {
		if (packet->isInstanceOf<PlayerAuthInputPacket>(AuthInputPacket)) {
			auto* authInputPacket = reinterpret_cast<PlayerAuthInputPacket*>(packet);
			if (epicStroke) {
				authInputPacket->pitch = (float)(rand() % 360);
				authInputPacket->yaw = (float)(rand() % 360);
				//authInputPacket->yawUnused = (float)(rand() % 360);
				authInputPacket->InputAD = (float)(rand() % 360);
				authInputPacket->InputWS = (float)(rand() % 360);
				Game.getLocalPlayer()->bodyYaw = (float)(rand() % 360);
				Game.getLocalPlayer()->pitch = (float)(rand() % 360);
				//Game.getLocalPlayer()->yawUnused1 = (float)(rand() % 360);
			}
			else {
				authInputPacket->pitch = (float)(counter % 360);
				authInputPacket->yaw = (float)(counter % 360);
				//authInputPacket->yawUnused = (float)(counter % 360);
				authInputPacket->InputAD = (float)(counter % 360);
				authInputPacket->InputWS = (float)(counter % 360);
				Game.getLocalPlayer()->pitch = (float)(counter % 360);
				Game.getLocalPlayer()->bodyYaw = (float)(counter % 360);
			//	Game.getLocalPlayer()->yawUnused1 = (float)(counter % 360);
			}
		}
	
	}
	
	
}
