#pragma once

#ifndef PERFORMANCE_TEST
//#define PERFORMANCE_TEST
#endif
#include "../SimpleMod/Command/CommandMgr.h"
#include "../SimpleMod/Config/ConfigManager.h"
#include "../SimpleMod/DrawUtils.h"
#include "../SimpleMod/Menu/Clickgui.h"
#include "../SimpleMod/Module/ModuleManager.h"
#include "../SDK/GameMode.h"
#include "../SDK/TextHolder.h"
#include "../Utils/TextFormat.h"

#include "MinHook/MinHook.h"
#include <d3d11.h>
#include <d3dcompiler.h>
#include <dxgi.h>
#include <intrin.h>
#include "../SDK/Entity.h"

#include "../SDK/CMoveInputHandler.h"
#include <thread>
#include <unordered_map>
#include "../SDK/C_EntityList.h"
#include <iostream>
#include "GameData.h"


using namespace std;
class VMTHook;
class FuncHook;

struct CoolSkinData {
};

class Hooks {
private:
	bool shouldRender = true;
public:

	char currentScreenName[100];
	std::vector<std::shared_ptr<FuncHook>> lambdaHooks;
	struct EntityListPointerHolder {
		Entity* ent;
		int addedTick;
	};
	std::vector<EntityListPointerHolder> entityList;
	__int32 RMBManager = 0;
	bool shouldLocalPlayerBeImmobile = false;

	static void Init();
	static void Restore();
	static void Enable();

private:
	static BOOL __stdcall hkWGLSwapBuffers(HDC hdc);
	static HRESULT __stdcall hkPresent11(IDXGISwapChain* pSwapChain, UINT SyncInterval, UINT Flags);
	static HRESULT __stdcall hkResizeBuffers(IDXGISwapChain* pSwapChain, UINT BufferCount, UINT Width, UINT Height, DXGI_FORMAT NewFormat, UINT SwapChainFlags);

	static void _fastcall  KeyMapHookCallback(uintptr_t* _this,uintptr_t edx,unsigned char key,bool isDown);
	static float _fastcall  GetGamma(uintptr_t* _this);
	static int _fastcall  MoveInputHandler_tick(C_MoveInputHandler* _this);
	static void _fastcall  entitylist(C_EntityList* Entitylist,uintptr_t edx,int a1);
	static void _fastcall  Player_tickWorldHook(Player* _this,uintptr_t edx,uintptr_t a1);
	static void _fastcall  ClientInstanceScreenModel_sendChatMessage(void* ecx,uintptr_t edx,TextHolder* text);

	static void _fastcall  entitybase(Entity* Entitylist);
	static void _fastcall Actor__setRot(Entity* _this,int edx, Vec2& angle);
	static __int32 _fastcall Actor_lerpMotion(Entity* _this,int edx, Vec3&);

	static void _fastcall LoopbackPacketSender_sendToServer(LoopbackPacketSender* a,uintptr_t edx, Packet* packet);

	static void _fastcall GameMode_startDestroyBlock(GameMode* _this, uintptr_t edx, Vec3i* a2, uint8_t face, int a4);
	static __int32 _fastcall GameMode_attack(GameMode* _this,int edx, Entity*);
	static float _fastcall GameMode_getPickRange(GameMode* _this,int edx, int a1,char a2);

	std::unique_ptr<FuncHook> OnTick;
	std::unique_ptr<FuncHook> Actor__setRotHook;
	std::unique_ptr<FuncHook> KeyMap;
	std::unique_ptr<FuncHook> GetGammaHook;
	std::unique_ptr<FuncHook> MoveInputHandler_tickHook;
	std::unique_ptr<FuncHook> Entitylist;
	std::unique_ptr<FuncHook> Entitybase;
	std::unique_ptr<FuncHook> Player_tickWorld;
	std::unique_ptr<FuncHook> Actor_lerpMotionHook;
	std::unique_ptr<FuncHook> GameMode_getPickRangeHook;
	std::unique_ptr<FuncHook> GameMode_attackHook;
	std::unique_ptr<FuncHook> GameMode_startDestroyBlockHook;
	std::unique_ptr<FuncHook> LoopbackPacketSender_sendToServerHook;
	std::unique_ptr<FuncHook> ClientInstanceScreenModel_sendChatMessageHook;

	std::unique_ptr<FuncHook> oPresent;
	std::unique_ptr<FuncHook> ResizeBuffers;

	std::unique_ptr<FuncHook> oWGLSwapBuffers;

};

extern Hooks g_Hooks;

class FuncHook {
public:
	void* funcPtr;
	void* funcReal;

	FuncHook(void* func, void* hooked) {
		funcPtr = func;

		// Check if the function pointer is valid
		if (IsBadReadPtr(funcPtr, sizeof(funcPtr))) {
			//		cout<<"Invalid function pointer!"<<endl;
			return;
		}

		MH_STATUS ret = MH_CreateHook(func, hooked, &funcReal);
		if (ret == MH_OK && (__int32)func > 10) {
			// Hook created successfully
		}
		else {
			//		cout<<"MH_CreateHook "<<ret<<endl;
		}
	};

	FuncHook(uintptr_t func, void* hooked) {
		funcPtr = reinterpret_cast<void*>(func);

		// Check if the function pointer is valid
		if (IsBadReadPtr(funcPtr, sizeof(funcPtr))) {
			//		cout<<"Invalid function pointer!"<<endl;
			return;
		}

		MH_STATUS ret = MH_CreateHook(funcPtr, hooked, &funcReal);
		if (ret == MH_OK && (__int32)funcPtr > 10) {
		}
		else {
			//			cout << "MH_CreateHook " << ret << endl;
		}
	};

	void enableHook(bool enable = true) {
		if (funcPtr != nullptr) {
			int ret = enable ? MH_EnableHook(funcPtr) : MH_DisableHook(funcPtr);
			if (ret != MH_OK) {
				//	cout<<"MH_EnableHook"<< ret<<endl;
			}
		}
		else {
			//			cout<<"enableHook() called with nullptr func!"<<endl;
		}
	}
	~FuncHook() { Restore(); }
	// Restore the hook
	void Restore() {
		if (funcPtr != nullptr) {
			MH_STATUS ret = MH_DisableHook(funcPtr);
			if (ret != MH_OK) {
				//				cout<<"MH_DisableHook"<<ret<<endl;
			}
		}
	}
	// Get the original function pointer with fastcall calling convention
	template <typename TRet, typename... TArgs>

	inline auto* GetFastcall() {
		using Fn = TRet(__fastcall*)(TArgs...);
		return reinterpret_cast<Fn>(funcReal);
	};

	template <typename TRet, typename... TArgs>
	inline auto* Getstdcall() {
		using Fn = TRet(__stdcall*)(TArgs...);
		return reinterpret_cast<Fn>(funcReal);
	};
};
