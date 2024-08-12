#pragma once
#include "Entity.h"
#include "LoopbackPacketSender.h"
class Minecraft {
private:
	char pad_0x0000[0xD8];  //0x0000
public:
	float* timer;       //0x00D8
	float* otherTimer;  //0x00E0

	void setTimerSpeed(float tps) {
		*this->timer = tps;
		*this->otherTimer = tps;
	}


};

class LevelRenderer {
public:
	Vec3& getOrigin() {
		return *(Vec3*)((char*)this + (0x93C));
	}
};
class ClientInstance;
class MinecraftGame {
private:
	char pad_0x0[0xE0];
public:
	bool canUseKeys;  //0xE4
private:
	virtual void Fun_01(void);
	virtual void Fun_02(void);
public:
	virtual ClientInstance* GetClientInstance();	
public:
	const bool canUseKeybinds() {
		return canUseKeys;
	};

};
class GuiData {
private:
	char pad_0x0[0x1C];
public:
	union {
		struct {
			float widthGame;   //0x0028
			float heightGame;  //0x002C
		};
		Vec2 windowSize;  //0x0028
	};
public:
	void displayClientMessageVA(const char* fmt, va_list lis, bool sendToInjector = true);

	void displayClientMessageF(const char* fmt, ...);
	void displayClientMessageNoSendF(const char* fmt, ...);
	void displayClientMessage(std::string* a2);
};
class ClientInstance{
private:
	char pad_0x0[0x68];
public:
	Minecraft* minecraft;  //0x6C
private:
	int int1;
public:
	class LevelRenderer* levelRenderer; //0xD0
private:
	int int2;
public:
	LoopbackPacketSender* loopbackPacketSender;  //0x7C
private:
	virtual void function_0(void); //0
	virtual void function_1(void); //1
	virtual void function_2(void); //2
	virtual void function_3(void); //3
	virtual void function_4(void); //4
	virtual void function_5(void); //5
public:
	virtual __int32 initGraphics(void); //6
private:
	virtual void function_7(void); //7
	virtual void function_8(void); //8
	virtual void function_9(void); //9
	virtual void function_10(void); //10
	virtual void function_11(void); //11
	virtual void function_12(void); //12
	virtual void function_13(void); //13
public:
	virtual __int32 resetPrimaryClient(void); //14
	virtual __int32 function_15(void); //15
private:
	virtual void function_16(void); //16
	virtual void function_17(void); //17
	virtual void function_18(void); //18
	virtual void function_19(void); //19
	virtual void function_20(void); //20
public:
	virtual __int32 startSubClientLateJoin(bool); //21
private:
	virtual void function_22(void); //22
	virtual void function_23(void); //23
	virtual void function_24(void); //24
	virtual void function_25(void); //25
	virtual void function_26(void); //26
public:
	virtual LocalPlayer* getCILocalPlayer(void);  //27
	virtual uintptr_t* GetMainScenestack(void); //28
private:
	virtual __int32 function_29(void); //29
	virtual __int32 function_30(void); //29
	virtual __int32 function_31(void); //29
	virtual __int32 function_32(void); //29
	virtual __int32 function_33(void); //29
	virtual __int32 function_34(void); //29
public:
	virtual __int32 Getchannelservice(uintptr_t xx); //29
private:
	virtual __int32 function_36(void); //29
	virtual __int32 function_37(void); //29
	virtual __int32 function_38(void); //29
	virtual __int32 function_39(void); //29
	virtual __int32 function_40(void); //29
public:
	GuiData* getGuiData() {
		return (GuiData*)*reinterpret_cast<__int64*>(reinterpret_cast<GuiData*>(reinterpret_cast<__int32>(this) + 0x4B0));
	};
	Vec3& getOrigin() {
		return *(Vec3*)((char*)this + (0x37c));
	}
	Vec2 getFov() {
		uintptr_t _this = reinterpret_cast<uintptr_t>(this);
		//vec2_t fov(fovX, fovY);
		Vec2 fov;
		fov.x = *reinterpret_cast<float*>(_this + 0x600);
		fov.y = *reinterpret_cast<float*>(_this + 0x614);
		return fov;
	}
	glmatrixf* getRefDef() {
		uintptr_t _this = reinterpret_cast<uintptr_t>(this);
		//logF("refderf %llX", _this + 0x258);
		return reinterpret_cast<glmatrixf*>(_this + 0x1BC);
	};

};

