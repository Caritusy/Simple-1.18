#include "PacketLogs.h"

PacketLogs::PacketLogs() :IModule(0x0, Category::MISC, "Record the game's data packets.") {
}

PacketLogs::~PacketLogs()
{
}

void PacketLogs::onDisable(){
	if (!printedAddresses.empty())
		printedAddresses.clear();
}

std::string PacketLogs::getModuleName()
{
	return "PacketLogs";
}

void PacketLogs::onSendPacket(Packet* packet, bool& cancelSend) {
#ifdef _DEBUG
	if (packet->isInstanceOf<C_MovePlayerPacket>(MovePlayerPacket)){
		static auto packets = reinterpret_cast<C_MovePlayerPacket*>(packet);
		Game.getClientInstance()->getGuiData()->displayClientMessageF(" Pos(X=%f Y=%f Z=%f) onGround=%i pitch=%f yaw=%f headYaw=%f entityRuntimeID=%i", packets->Position.x, packets->Position.y, packets->Position.z, (int)packets->onGround, packets->pitch, packets->yaw, packets->headYaw,packets->entityRuntimeID);
		LOG(INFO) << "pos=" << packets->Position.x<< packets->Position.y<< packets->Position.z<< "pitch= " << packets->pitch << "yaw= " << packets->headYaw << "entityRuntimeID= " << packets->entityRuntimeID<<"packet= "<<packet;
		return;
	}
	/*if (packet->isInstanceOf<PlayerAuthInputPacket>(PlayerAuthInput)){
		static auto packets = reinterpret_cast<PlayerAuthInputPacket*>(packet);
		Game.getClientInstance()->getGuiData()->displayClientMessageF(" Pos(X=%f Y=%f Z=%f) onGround=%i pitch=%f yaw=%f headYaw=%f yawUnused=%i InputAD%i InputWS%i", packets->pos.x, packets->pos.y, packets->pos.z, (int)packets->onGround, packets->pitch, packets->yaw, packets->yawUnused,packets->InputAD,packets->InputWS);
		printf(" Pos(X=%f Y=%f Z=%f) onGround=%i pitch=%f yaw=%f headYaw=%f yawUnused=%i InputAD%i InputWS%i", packets->pos.x, packets->pos.y, packets->pos.z, (int)packets->onGround, packets->pitch, packets->yaw, packets->yawUnused,packets->InputAD,packets->InputWS);
		return;
	}*/
	if (packet->isInstanceOf<PlayerActionPacket>(playerActionPacket)&& UTime.hasTimedElapsed(500,true)) {
		static auto packets = reinterpret_cast<PlayerActionPacket*>(packet);
		Game.getClientInstance()->getGuiData()->displayClientMessageF(" action=%d face=%d blockPos(X=%d Y=%d Z=%d)", packets->action, packets->face, packets->blockPosition.x, packets->blockPosition.y, packets->blockPosition.z);
		LOG(INFO) << "action= " << packets->action << " face= " << packets->face << " blockPos= " << packets->blockPosition.x<< packets->blockPosition.y<< packets->blockPosition.z<<" packet= "<<packet;
		return;
	}	
	if (packet->isInstanceOf<C_TextPacket>(TextPacket)) {
		auto packets = reinterpret_cast<C_TextPacket*>(packet);
		Game.getClientInstance()->getGuiData()->displayClientMessageF("messageType=%i message=%s sourceName=%s", packets->messageType,packets->message.getText(),packets->sourceName.getText());
		LOG(INFO) << "messageTypr= " << packets->messageType << "message= " << packets->message.getText() << "sourcename= " << packets->sourceName.getText() << "packet= " << packet;
		return;
	}
	if (packet->isInstanceOf<LevelSoundEventPacket>(levelSoundEventPacket)) {
		auto packets = reinterpret_cast<LevelSoundEventPacket*>(packet);
		Game.getClientInstance()->getGuiData()->displayClientMessageF("sound=%i extraData=%i disableRelativeVolume=%i isBabyMod=%i Pos(X=%f,Y=%f,Z=%f)", packets->sound, packets->extraData, (int)packets->disableRelativeVolume, (int)packets->isBabyMod, packets->pos.x, packets->pos.y, packets->pos.z);
		LOG(INFO) << "sound= " << packets->sound << "extraData= " << packets->extraData << "disableRelativeVolume= " << packets->disableRelativeVolume << "isBabymod= " << packets->isBabyMod << "pos= " << packets->pos.x<< packets->pos.y<< packets->pos.z<<"packet= "<<packet;
		return;
	}
	if (packet->isInstanceOf<CommandRequestPacket>(commandRequestPacket)) {
		auto packets = reinterpret_cast<CommandRequestPacket*>(packet);
		Game.getClientInstance()->getGuiData()->displayClientMessageF("command=%s", packets->Command.getText());
		LOG(INFO) << "command=" << packets->Command.getText() <<"packet= " << packet;
		return;
	}
	if (packet->isInstanceOf<SetPlayerGameTypePacket>(setPlayerGameTypePacket)) {
		auto packets = reinterpret_cast<SetPlayerGameTypePacket*>(packet);
		Game.getClientInstance()->getGuiData()->displayClientMessageF("Gamemode=%i", packets->gamemode);
		LOG(INFO) << "Gamemode= " << packets->gamemode;
		return;
	}

	if (printedAddresses.find(reinterpret_cast<uintptr_t>(packet)) == printedAddresses.end()) {
		static int i = 0;
		Game.getGuiData()->displayClientMessageF("%s [%d] packet:%s %x vtable{%x}", GRAY,i, GREEN, packet, *((uintptr_t*)packet));i++;
		LOG(INFO) << "packet= " << packet << "vatble= " << *((uintptr_t*)packet);
		printedAddresses.insert(reinterpret_cast<uintptr_t>(packet));
	}

#endif  // DEBUG
}