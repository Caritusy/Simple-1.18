#include "Velocity.h"

Velocity::Velocity() : IModule(0, Category::MOVEMENT, "Don't ever take knockback again.") {
	registerFloatSetting("Linear Modifier", &xModifier, xModifier, -5.f, 5.f);
	registerFloatSetting("Height Modifier", &yModifier, yModifier, -5.f, 5.f);
}

Velocity::~Velocity(){
}

std::string Velocity::getModuleName(){
	return ("Velocity");
}

void Velocity::onSendPacket(Packet* packet, bool& cancelSend){
	if (packet->isInstanceOf<PlayerAuthInputPacket>(AuthInputPacket)) {
		auto* authInputPacket = reinterpret_cast<PlayerAuthInputPacket*>(packet);
		authInputPacket->Velocity = Game.getLocalPlayer()->velocity.lerp(authInputPacket->Velocity, xModifier, yModifier, xModifier);
	}
}
