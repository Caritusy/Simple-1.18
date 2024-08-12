#pragma once
#include "IModule.h"
#include "../ModuleManager.h"
class PacketLogs:public IModule{
private:
	TimerUtil UTime;

	std::unordered_set<uintptr_t> printedAddresses;

	C_MovePlayerPacket MovePlayerPacket;
	PlayerActionPacket playerActionPacket;
	C_TextPacket TextPacket;
	LevelSoundEventPacket levelSoundEventPacket;
	CommandRequestPacket commandRequestPacket;
	SetPlayerGameTypePacket setPlayerGameTypePacket;
	PlayerAuthInputPacket PlayerAuthInput;
public:
	PacketLogs();
	~PacketLogs();
	virtual void onDisable() override;
	virtual std::string getModuleName() override;
	virtual void onSendPacket(Packet* packet, bool& cancelSend) override;
};

