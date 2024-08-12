#include "superkb.h"

superkb::superkb():IModule(0x0,Category::COMBAT,"Knock back farther."){
}

superkb::~superkb(){
}

std::string superkb::getModuleName()
{
	return "superkb";
}

void superkb::onAttack(Entity* ent){

		PlayerAction.action = 9;
		PlayerAction.entityRuntimeId = Game.getLocalPlayer()->EntityRuntimeid;
		Game.getClientInstance()->loopbackPacketSender->sendToServer(&PlayerAction);
}
