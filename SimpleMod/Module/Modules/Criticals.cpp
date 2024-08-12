#include "Criticals.h"

Criticals::Criticals() : IModule(0, Category::COMBAT, "Each hit becomes a critical hit.") {
    registerIntSetting("hurttime", &hurttime, hurttime, 0, 5);
}

Criticals::~Criticals()
{
}

std::string Criticals::getModuleName()
{
	return ("Criticals");
}

void Criticals::onSendPacket(Packet* packet, bool& cancelSend)
{
}

void Criticals::onAttack(Entity* attackEnt){
	PlayerAction.action = 8;
	PlayerAction.entityRuntimeId = Game.getLocalPlayer()->EntityRuntimeid;
	Game.getClientInstance()->loopbackPacketSender->sendToServer(&PlayerAction);
	/*static int a = 0;
	++a;
	if (a >= 2) {
		a = 0;
		return;
	}
	if (attackEnt->hurttime > hurttime)
		return;
	LocalPlayer* localPlayer = Game.getLocalPlayer();
	Vec3* localPlayerPos = localPlayer->getPos();
	PlayerAuthInputPacket PlayerAuthInpu;
	PlayerAuthInpu.onGround = false;
	PlayerAuthInpu.pos = Vec3(localPlayerPos->x, localPlayerPos->y + RandomFloat(0.09f, 0.3f), localPlayerPos->z);
	Game.getClientInstance()->loopbackPacketSender->sendToServer(&PlayerAuthInpu);
	PlayerAuthInpu.pos = Vec3(localPlayerPos->x, localPlayerPos->y + RandomFloat(0.001f, 0.09f), localPlayerPos->z);
	Game.getClientInstance()->loopbackPacketSender->sendToServer(&PlayerAuthInpu);*/
}
