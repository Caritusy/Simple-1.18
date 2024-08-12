#include "Packet.h"

#include "../Utils/Utils.h"

C_MovePlayerPacket::C_MovePlayerPacket(){
	static uintptr_t** MovePacketVtable = 0x0;
	if (MovePacketVtable == 0x0) {
		MovePacketVtable = (uintptr_t**)GetOffsetFromSig("C7 07 ? ? ? ? E8 ? ? ? ? 8B 06 8B CE FF 50 60 F3 0F 7E 00", 2);
#ifdef _DEBUG
		if (MovePacketVtable == 0x0)
			__debugbreak();
#endif
	}
	memset(this, 0, sizeof(C_MovePlayerPacket));
	vTable = MovePacketVtable;
}

C_MovePlayerPacket::C_MovePlayerPacket(LocalPlayer* player, Vec3 pos){
	static uintptr_t** MovePacketVtable = 0x0;
	if (MovePacketVtable == 0x0) {
		MovePacketVtable = (uintptr_t**)GetOffsetFromSig("C7 07 ? ? ? ? E8 ? ? ? ? 8B 06 8B CE FF 50 60 F3 0F 7E 00", 2);
#ifdef _DEBUG
		if (MovePacketVtable == 0x0)
			__debugbreak();
#endif
	}
	memset(this, 0, sizeof(C_MovePlayerPacket));
	vTable = MovePacketVtable;
	entityRuntimeID = player->EntityRuntimeid;
	Position = pos;
	pitch = player->pitch;
	yaw = player->yaw;
	headYaw = player->yaw;
	onGround = true;
}

C_TextPacket::C_TextPacket(){
	static uintptr_t** textPacketVtable = 0x0;
	if (textPacketVtable == 0x0) {
		 textPacketVtable = (uintptr_t**)GetOffsetFromSig("C7 06 ? ? ? ? 88 46 ? E8 ? ? ? ? FF 75 ? 8D 4E ? C6 45 FC ? E8 ? ? ? ? FF 75 ? 8D 4E ? C6",2);
#ifdef _DEBUG
		if (textPacketVtable == 0x0)
			__debugbreak();
#endif
	}
	memset(this, 0, sizeof(C_TextPacket));
	vTable = textPacketVtable;
}


LevelSoundEventPacket::LevelSoundEventPacket(){
	uintptr_t** LevelSoundEventVtable = 0x0;
	if (LevelSoundEventVtable == 0x0) {
		LevelSoundEventVtable = (uintptr_t**)GetOffsetFromSig("C7 06 ? ? ? ? 8D 4E 3C C7 46 ? A7 01 00 00 C7 46 ? 00 00 00 00 C7 46", 2);
#ifdef _DEBUG
		if (LevelSoundEventVtable == 0x0)
			__debugbreak();
#endif
	}
	memset(this, 0, sizeof(LevelSoundEventPacket));
	vTable = LevelSoundEventVtable;
	this->entityType.setText("minecraft:player");
}

PlayerActionPacket::PlayerActionPacket(){
	uintptr_t** PlayerActionPacketvtable = 0x0;
	if (PlayerActionPacketvtable == 0x0) {
		PlayerActionPacketvtable = (uintptr_t**)GetOffsetFromSig("C7 07 ? ? ? ? 8B 70 08 8B 50 04 8B 00 89 47 28 0F B6 45 10 89 77 30", 2);
#ifdef _DEBUG
		if (PlayerActionPacketvtable == 0x0)
			__debugbreak();
#endif
	}
	memset(this, 0, sizeof(PlayerActionPacket));
	vTable = PlayerActionPacketvtable;
}

SetPlayerGameTypePacket::SetPlayerGameTypePacket(){
	uintptr_t** SetPlayerGameTypePacketvtable = 0x0;
	if (SetPlayerGameTypePacketvtable == 0x0) {
		SetPlayerGameTypePacketvtable = (uintptr_t**)GetOffsetFromSig("C7 06 58 ? ? ? 8B C6 C7 46 28 FF FF FF FF 5E 8B E5 5D C3", 2);
#ifdef _DEBUG
		if (SetPlayerGameTypePacketvtable == 0x0)
			__debugbreak();
#endif
	}
	memset(this, 0, sizeof(SetPlayerGameTypePacket));
	vTable = SetPlayerGameTypePacketvtable;
}

PlayerAuthInputPacket::PlayerAuthInputPacket(){
	static uintptr_t** PlayerAuthInputPacketVtable = 0x0;
	if (PlayerAuthInputPacketVtable == 0x0) {
		PlayerAuthInputPacketVtable = (uintptr_t**)GetOffsetFromSig("C7 06 ? ? ? ? 0F 57 C0 C7 46 28 00 00 00 00 8B C6 C7 46 2C 00 00 00 00 C7", 2);
#ifdef _DEBUG
		if (PlayerAuthInputPacketVtable == 0x0)
			__debugbreak();
#endif
	}
	memset(this, 0, sizeof(PlayerAuthInputPacket));
	vTable = PlayerAuthInputPacketVtable;
}

PlayerAuthInputPacket::PlayerAuthInputPacket(Vec3 pos,LocalPlayer* player){
	static uintptr_t** PlayerAuthInputPacketVtable = 0x0;
	if (PlayerAuthInputPacketVtable == 0x0) {
		PlayerAuthInputPacketVtable = (uintptr_t**)GetOffsetFromSig("C7 06 ? ? ? ? 0F 57 C0 C7 46 28 00 00 00 00 8B C6 C7 46 2C 00 00 00 00 C7", 2);
#ifdef _DEBUG
		if (PlayerAuthInputPacketVtable == 0x0)
			__debugbreak();
#endif
	}
	memset(this, 0, sizeof(PlayerAuthInputPacket));
	vTable = PlayerAuthInputPacketVtable;
	this->pos = pos;
	this->pitch = player->pitch;
	this->yaw =player->yaw;
	this->yawUnused = player->yaw;
	this->onGround = true;
	this->InputAD = player->pitch;
	this->InputWS = player->yaw;
}

RespawnPacket::RespawnPacket(){
	static uintptr_t** RespawnPacketVtable = 0x0;
	if (RespawnPacketVtable == 0x0) {
		RespawnPacketVtable = (uintptr_t**)GetOffsetFromSig("C7 06 ? ? ? ? 8B C6 C7 46 28 00 00 00 00 C7 46 2C 00 00 00 00 C7 46 30 00 00 00 00 C6 46 34 00 C7 46 38 00 00 00 00 C7 46 3C 00 00 00 00 5E 8B E5 5D C3", 2);
#ifdef _DEBUG
		if (RespawnPacketVtable == 0x0)
			__debugbreak();
#endif
	}
	memset(this, 0, sizeof(PlayerAuthInputPacket));
	vTable = RespawnPacketVtable;
}

TextHolder* Packet::getName()
{
	return nullptr;
}

SubChunkRequestPackePacket::SubChunkRequestPackePacket(){
	static uintptr_t** SubChunkRequestPackePacketVtable = 0x0;
	if (SubChunkRequestPackePacketVtable == 0x0) {
		SubChunkRequestPackePacketVtable = (uintptr_t**)GetOffsetFromSig("C7 07 ? ? ? ? 89 47 28 C7 47 2C 00 00 00 00 C7", 2);
#ifdef _DEBUG
		if (SubChunkRequestPackePacketVtable == 0x0)
			__debugbreak();
#endif
	}
	memset(this, 0, sizeof(SubChunkRequestPackePacket));
	vTable = SubChunkRequestPackePacketVtable;
}

EventPacketPacket::EventPacketPacket(){
	static uintptr_t** EventPacketPacketVtable = 0x0;
	if (EventPacketPacketVtable == 0x0) {
		EventPacketPacketVtable = (uintptr_t**)GetOffsetFromSig("", 2);
#ifdef _DEBUG
		if (EventPacketPacketVtable == 0x0)
			__debugbreak();
#endif
	}
	memset(this, 0, sizeof(SubChunkRequestPackePacket));
	vTable = EventPacketPacketVtable;
}

MobEquipmentPacket::MobEquipmentPacket(){
	static uintptr_t** MobEquipmentPacketVtable = 0x0;
	if (MobEquipmentPacketVtable == 0x0) {
		MobEquipmentPacketVtable = (uintptr_t**)GetOffsetFromSig("C7 03 ? ? ? ? 89 43 28 89 53 2C 89 7D EC E8 ? ? ? ? 66 8B 46 30", 2);
#ifdef _DEBUG
		if (MobEquipmentPacketVtable == 0x0)
			__debugbreak();
#endif
	}
	memset(this, 0, sizeof(SubChunkRequestPackePacket));
	vTable = MobEquipmentPacketVtable;
}

pyrpcpackettPacket::pyrpcpackettPacket(){
	static uintptr_t** pyrpcpackettPacketVtable = 0x0;
	if (pyrpcpackettPacketVtable == 0x0) {
		pyrpcpackettPacketVtable = (uintptr_t**)GetOffsetFromSig("C7 06 ? ? ? ? C7 01 00 00 00 00 C7 41 10 00 00 00 00 C7 41 14 0F 00 00 00 6A 00 68 56 2F 84 04 C6 45 FC 02 E8 ? ? ? ? C7 46 40 00 00 00 00 EB 02 33 FF", 2);
#ifdef _DEBUG
		if (pyrpcpackettPacketVtable == 0x0)
			__debugbreak();
#endif
	}
	memset(this, 0, sizeof(SubChunkRequestPackePacket));
	vTable = pyrpcpackettPacketVtable;
}

CommandRequestPacket::CommandRequestPacket(){
	static uintptr_t** CommandRequestPacketVtable = 0x0;
	if (CommandRequestPacketVtable == 0x0) {
		CommandRequestPacketVtable = (uintptr_t**)GetOffsetFromSig("C7 06 ? ? ? ? C7 46 28 00 00 00 00 C7 45 FC 00 00 00 00 C7 46 38 00 00 00 00 C7 46 3C 0F 00 00 00 C6 46 28 00 8D 4E 40 C6 45 FC 01", 2);
#ifdef _DEBUG
		if (CommandRequestPacketVtable == 0x0)
			__debugbreak();
#endif
	}
	memset(this, 0, sizeof(CommandRequestPacket));
	vTable = CommandRequestPacketVtable;
}

ChangeModelPacket::ChangeModelPacket(){
	static uintptr_t** ChangeModelPacketVtable = 0x0;
	if (ChangeModelPacketVtable == 0x0) {
		ChangeModelPacketVtable = (uintptr_t**)GetOffsetFromSig("C7 06 ? ? ? ? C7 01 00 00 00 00 C7 41 10 00 00 00 00 C7 41 14 0F 00 00 00 C6 01 00 8D 45 0C C6 45 FC 02 3B C8", 2);
#ifdef _DEBUG
		if (ChangeModelPacketVtable == 0x0)
			__debugbreak();
#endif
	}
	memset(this, 0, sizeof(ChangeModelPacket));
	vTable = ChangeModelPacketVtable;
}
