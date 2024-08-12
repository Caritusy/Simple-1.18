#pragma once
#include "../Utils/HMath.h"
#include "Entity.h"
#include "TextHolder.h"
#include "../Utils/logger.h"
#pragma pack(push, 4)
class Packet {
public:
	uintptr_t** vTable;  //0x0000
public:
	TextHolder* getName();
	template <class T>
	bool isInstanceOf(T& packet) {
		//T packet;
		if (packet.vTable == this->vTable)
			return true;
		else
			return false;
	}
};
class RespawnPacket : public Packet {
public:
	RespawnPacket();
public:
	char pad_0x0[0x30];
	int int1;
	bool Respawn;
};
class PlayerAuthInputPacket : public Packet {
public:
	PlayerAuthInputPacket();
	PlayerAuthInputPacket(Vec3 pos, LocalPlayer* player);
private:
	char pad_0x0[0x24];
public:
	float pitch;              //0x24
	float yaw;                //0x28
	Vec3 pos;
	float yawUnused; 
	Vec3 Velocity;
	bool onGround;
	float InputAD;
	float InputWS;
	char pad_0x54[0x20];
	uint32_t inputMode;
	int zero;
	int one;
	int two;
	int counter;
	char pad_0xfill[0x200];
};class MobEquipmentPacket : public Packet {
public:
	MobEquipmentPacket();
};
class SubChunkRequestPackePacket : public Packet {
public:
	SubChunkRequestPackePacket();
};
class EventPacketPacket : public Packet {
public:
	EventPacketPacket();
};class pyrpcpackettPacket : public Packet {
public:
	pyrpcpackettPacket();
};class ChangeModelPacket : public Packet {
public:
	ChangeModelPacket();
private:
	char pad_0x0[0x24];
public:
};

class SetPlayerGameTypePacket : public Packet {
public:
	SetPlayerGameTypePacket();
	char pad_0x0[0x24];
	__int32 gamemode;
	char fill[0x200];
};
class CommandRequestPacket : public Packet {
public:
	CommandRequestPacket();
private:
	char pad_0x0[0x24];
public:
	TextHolder Command;
private:
	uint32_t unk[2];
	TextHolder text;
	__int32 id;
	uint16_t pad;
	char fill2[0x500];
};

class PlayerActionPacket : public Packet {
public:
	PlayerActionPacket();
private:
	char pad_0[0x24];
public:
	Vec3i blockPosition;
	__int32 face;                 // 0x34
	__int32 action;               // 0x38
	char fill[4];
	__int32 entityRuntimeId;  // 0x40
	char fill2[1000];
};

class LevelSoundEventPacket : public Packet {
private:
	char pad_0x4[0x24];
public:
	int sound;           //0x28
	Vec3 pos;          //0x2C
	int extraData = -1;  //0x38
private:
	int unknown = 0;  //0x3C
public:
	TextHolder entityType;               //0x40
	bool isBabyMod = false;              //0x60
	bool disableRelativeVolume = false;  //0x61
	LevelSoundEventPacket();
};

class C_TextPacket : public Packet {
public:
	C_TextPacket();
private:
	char pad_0x4[0x24];
public:
	unsigned __int8 messageType;  // 0x28
	TextHolder sourceName;           // 0x2c
	//char pad_2c[0x14];
	TextHolder message;              // 0x44
	unsigned char field_24222[24];   // 0x70
	bool translationNeeded = false;  // 0x88

	unsigned char ga2p[7];  // 0x89
	TextHolder platformChatId;
	char fill[200];
};

class C_MovePlayerPacket : public Packet {
public:
	C_MovePlayerPacket();
	C_MovePlayerPacket(LocalPlayer* player, Vec3 pos);
private:
	char pad_0x0[0x24];
public:
	__int32 entityRuntimeID;
	__int32 int1;
	Vec3 Position;          //0x30
	float pitch;              //0x3c
	float yaw;                //0x40
	float headYaw;            //0x44
	bool onGround;
	char fill[0x200];
};
#pragma pack(pop)
