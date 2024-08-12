#pragma once
#pragma pack(push, 4)
class C_MoveInputHandler{
private:
	char pad_0x0[0x4];
public:
	float sideMovement;//0x4
	float forwardMovement; //0x8
private:
	char pad_0x8[0x3C];
public:
	bool isSneakDown; //0x0048
private:
	char pad_0x4C[0x8];
public:
	bool isSprintkey;
private:
	char pad_0x5C[0x28];
public:
	bool isJumping; //0x0084
	bool autoJumpInWater; // 88
};
#pragma pack(pop)
