#include <windows.h>
#include <algorithm>
#include <iomanip>
#include "../Utils/easylogging++.h"
#include "../Utils/Utils.h"
#include "Hooks.h"
#include "../SimpleMod/Loader.h"
using namespace std;
Hooks g_Hooks;
void Hooks::Init() {
	LOG(INFO) << "Setting up Hooks...";
	{
		{
			uintptr_t keyMap = FindSignature("55 8B EC 8B 4D ? 83 EC ? 85 C9 0F 88");
			g_Hooks.KeyMap = std::make_unique<FuncHook>(keyMap, Hooks::KeyMapHookCallback);
			uintptr_t fullbright = FindSignature("55 8B EC 51 80 B9 8D 09 00 00 00 8D 55 FC 8B 01 74 18");
			g_Hooks.GetGammaHook = std::make_unique<FuncHook>(fullbright, Hooks::GetGamma);
			uintptr_t _Entitylist = FindSignature("55 8B EC 8B 01 53 8B 5D ? FF 90 ? ? ? ? 84 DB 74 0A 3B D8");
			g_Hooks.Entitylist = std::make_unique<FuncHook>(_Entitylist, Hooks::entitylist);
			uintptr_t _sendChatMessage = FindSignature("55 8B EC 6A FF 68 ? ? ? ? 64 A1 ? ? ? ? 50 81 EC ? ? ? ? A1 ? ? ? ? 33 C5 89 45 F0 53 56 57 50 8D 45 F4 64 A3 ? ? ? ? 8B F1 89 75 EC 8B 4E 10 8B 45 08");
			g_Hooks.ClientInstanceScreenModel_sendChatMessageHook = std::make_unique<FuncHook>(_sendChatMessage, Hooks::ClientInstanceScreenModel_sendChatMessage);
			uintptr_t Player_tickWorldHook = FindSignature("55 8B EC 6A FF 68 ? ? ? ? 64 A1 ? ? ? ? 50 81 EC ? ? ? ? A1 ? ? ? ? 33 C5 89 45 F0 56 57 50 8D 45 F4 64 A3 ? ? ? ? 8B F1 89 75 D4 80 BE ? ? ? ? ? 0F 84 ? ? ? ?	 E8 ? ? ? ? 8B C8 8B 10");
			g_Hooks.Player_tickWorld = std::make_unique<FuncHook>(Player_tickWorldHook, Hooks::Player_tickWorldHook);
		}

		{
			if (Game.getClientInstance()->loopbackPacketSender != nullptr) {
				uintptr_t** packetSenderVtable = reinterpret_cast<uintptr_t**>(*(uintptr_t*)Game.getClientInstance()->loopbackPacketSender);
				if (packetSenderVtable == nullptr)
					LOG(INFO) << "LoopbackPacketSenderVtable is invalid";
				else {
					g_Hooks.LoopbackPacketSender_sendToServerHook = std::make_unique<FuncHook>(packetSenderVtable[2], Hooks::LoopbackPacketSender_sendToServer);
					//g_Hooks.LoopbackPacketSender_sendToClientHook = std::make_unique<FuncHook>(packetSenderVtable[4], Hooks::LoopbackPacketSender_sendToClient); //I use the second sendToClient
				}
			}	LOG(DEBUG) << "packetSenderVtable hook completion!";

			{
				uintptr_t** localPlayerVtable = (uintptr_t**)GetOffsetFromSig("C7 06 ? ? ? ? 8B 01 FF 90 74 04 00 00 6A 00 8B 08 8B 51 28 8B C8 FF D2", 2);
				LOG(DEBUG) << "localPlayerVtable: " << std::hex << localPlayerVtable;
				if (localPlayerVtable == 0x0)
					LOG(INFO) << "LocalPlayer signature not working!!!";
				else {
					g_Hooks.Actor__setRotHook = std::make_unique<FuncHook>(localPlayerVtable[29], Hooks::Actor__setRot);
					g_Hooks.Actor_lerpMotionHook = std::make_unique<FuncHook>(localPlayerVtable[48], Hooks::Actor_lerpMotion);
					g_Hooks.Entitybase = std::make_unique<FuncHook>(localPlayerVtable[51], Hooks::entitybase);
				}
			}	LOG(DEBUG) << "localPlayerVtable hook completion!";

			{
				uintptr_t** GamemodeVtable = (uintptr_t**)GetOffsetFromSig("C7 06 ? ? ? ? 0F 57 C0 89 7E 08 C7 46 0C FF FF FF FF C7 46 10 FF FF FF FF C7 46 14 FF FF FF FF F2 0F 11 46 28", 2);
				LOG(DEBUG) << "GamemodeVtable: " << std::hex << GamemodeVtable;
				if (GamemodeVtable == 0x0)
					LOG(INFO) << "Gamemode  signature not working!!!";
				else {
					g_Hooks.GameMode_startDestroyBlockHook = std::make_unique<FuncHook>(GamemodeVtable[1], Hooks::GameMode_startDestroyBlock);
					g_Hooks.GameMode_getPickRangeHook = std::make_unique<FuncHook>(GamemodeVtable[10], Hooks::GameMode_getPickRange);
					g_Hooks.GameMode_attackHook = std::make_unique<FuncHook>(GamemodeVtable[14], Hooks::GameMode_attack);
				}
			}	LOG(DEBUG) << "GamemodeVtable hook completion!";
			{
				uintptr_t** MoveInputHandler = (uintptr_t**)GetOffsetFromSig("C7 46 04 ? ? ? ? 8B C7 89 37 5F 5E 8B E5 5D C3 C7 07 00 00 00 00", 3);
				LOG(DEBUG) << "MoveInputHandler vtable: " << std::hex << MoveInputHandler;
				if (MoveInputHandler == 0x0)
					LOG(INFO) << "MoveInputHandler  signature not working!!!";
				else
					g_Hooks.MoveInputHandler_tickHook = std::make_unique<FuncHook>(MoveInputHandler[9], Hooks::MoveInputHandler_tick);
			}	LOG(DEBUG) << "MoveInputHandlervtable hook completion!";

			{
/*				if (GetModuleHandleA("d3d11.dll")) {
					uintptr_t** pSwapChainvtable = reinterpret_cast<uintptr_t**>(*(uintptr_t*)GameData::getoPresent());
					if (pSwapChainvtable == 0x0)LOG(INFO) << "pSwapChain  signature not working!!!";
					else {
						g_Hooks.oPresent = std::make_unique<FuncHook>(pSwapChainvtable[8], hkPresent11);
						g_Hooks.ResizeBuffers = std::make_unique<FuncHook>(pSwapChainvtable[13], hkResizeBuffers);
					}
				}
				else*/ if (GetModuleHandleA("opengl32.dll")) {
					uintptr_t oWGLSwapBuffers = (uintptr_t)GetProcAddress(GetModuleHandleA("opengl32.dll"), "wglSwapBuffers");
					if (oWGLSwapBuffers == 0x0)
						LOG(INFO) << "oWGLSwapBuffers  signature not working!!!";
					else {
						g_Hooks.oWGLSwapBuffers = std::make_unique<FuncHook>(oWGLSwapBuffers, hkWGLSwapBuffers);
					}
				}
			}
		}
	}
	LOG(INFO) << "Hooks initialized";
}

void Hooks::Restore() {
	MH_DisableHook(MH_ALL_HOOKS);
	LOG(INFO) << "DisableHook";
	Sleep(10);
}

void Hooks::Enable() {
	LOG(INFO) << "Hooks enabled";
	MH_EnableHook(MH_ALL_HOOKS);
	Game.getClientInstance()->getGuiData()->displayClientMessageF(u8"%s[SimpleMod] >> 加载成功 ✓", GREEN);

	Game.getClientInstance()->getGuiData()->displayClientMessageF(u8"%s[SimpleMod] >> 交流群: 320443172 & bug反馈|建议:Developer-QwQ@outlook.com", GREEN);
}

void  Hooks::entitylist(C_EntityList* Entitylist, uintptr_t edx, int a1) {
	static auto oFunc = g_Hooks.Entitylist->GetFastcall<void, C_EntityList*, uintptr_t, int>();
	GameMode* gm = Game.getGameMode();
	if (gm != nullptr) moduleMgr->onTick(gm);
	GameData::EntityList_tick(Entitylist);
	oFunc(Entitylist, edx, a1);
}

void  Hooks::entitybase(Entity* ent) {
	static auto oFunc = g_Hooks.Entitybase->GetFastcall<void, Entity*>();
	LocalPlayer* player = Game.getLocalPlayer();
	if (!player || ent == nullptr) return oFunc(ent);

	static int tickCountThen = 0;
	int tickCountNow = *(int*)((__int32)player->getlevel() + 0x6B0);

	if (tickCountNow != tickCountThen) {
		g_Hooks.entityList.clear();
		tickCountThen = tickCountNow;
	}
	moduleMgr->onBaseTick(ent);
	if (ent->ticksAlive > 0) {
		EntityListPointerHolder e;
		e.addedTick = tickCountNow;
		e.ent = ent;
		bool found = false;
		for (auto& entity : g_Hooks.entityList) {
			if (entity.ent == ent) {
				found = true;
				break;
			}
		}
		if (!found)
			g_Hooks.entityList.push_back(e);
	}
	return oFunc(ent);
}

void _fastcall Hooks::Actor__setRot(Entity* _this, int edx, Vec2& angle) {
	static auto func = g_Hooks.Actor__setRotHook->GetFastcall<void, Entity*, int, Vec2&>();
	static auto killauraMod = moduleMgr->getModule<Killaura>();
	static auto freelookMod = moduleMgr->getModule<Freelook>();
	//static auto freecamMod = moduleMgr->getModule<Freecam>();
	if (_this == Game.getLocalPlayer()) {
		/*if (freecamMod->isEnabled()) {
			freecamMod->yaw = angle.y;
			angle = { freecamMod->initialViewAngles.x, freecamMod->initialViewAngles.y };
		}*/
		if (killauraMod->isEnabled() && !killauraMod->targetListEmpty && killauraMod->rotations) angle = killauraMod->angle;
		if (freelookMod->isEnabled()) angle = freelookMod->oldPos;
	}
	func(_this, edx, angle);
}

void _fastcall Hooks::KeyMapHookCallback(uintptr_t* _this, uintptr_t edx, unsigned char key, bool isDown) {
	static auto oFunc = g_Hooks.KeyMap->GetFastcall<void, uintptr_t*, uintptr_t, unsigned char, bool>();
	bool shouldCancel = false;
	GameData::keys[key] = isDown;
	moduleMgr->onKey((int)key, isDown, shouldCancel);
	moduleMgr->onKeyUpdate((int)key, (isDown && GameData::canUseMoveKeys()));
	//	Game.getClientInstance()->getGuiData()->displayClientMessageF("kiy=%i", key);
	if (shouldCancel) return;
	return oFunc(_this, edx, key, isDown);
}

float _fastcall Hooks::GetGamma(uintptr_t* _this) {
	static auto ofunc = g_Hooks.GetGammaHook->GetFastcall<float, uintptr_t*>();
	static auto fullbright = moduleMgr->getModule<FullBright>();
	if (fullbright->isEnabled())
		return fullbright->intensity;
	return ofunc(_this);
}

int _fastcall Hooks::MoveInputHandler_tick(C_MoveInputHandler* _this) {
	static auto oTick = g_Hooks.MoveInputHandler_tickHook->GetFastcall<int, C_MoveInputHandler*>();
	moduleMgr->onMove(_this);
	return oTick(_this);
}

BOOL __stdcall Hooks::hkWGLSwapBuffers(HDC hdc) {
	static auto oWGLSwapBuffers = g_Hooks.oWGLSwapBuffers->Getstdcall<BOOL, HDC>();
	GuiData* dat = Game.getClientInstance()->getGuiData();
	DrawUtils::setCtx(dat);
	opengl::init(hdc);
	return oWGLSwapBuffers(hdc);
}

HRESULT __stdcall Hooks::hkPresent11(IDXGISwapChain* pSwapChain, UINT SyncInterval, UINT Flags) {
	static auto oTick = g_Hooks.oPresent->Getstdcall<HRESULT, IDXGISwapChain*, UINT, UINT>();
	GuiData* dat = Game.getClientInstance()->getGuiData();
	DrawUtils::setCtx(dat);
	D3D11::init(pSwapChain, SyncInterval, Flags);
	return oTick(pSwapChain, SyncInterval, Flags);
}

HRESULT __stdcall Hooks::hkResizeBuffers(IDXGISwapChain* pSwapChain, UINT BufferCount, UINT Width, UINT Height, DXGI_FORMAT NewFormat, UINT SwapChainFlags) {
	static auto oFun = g_Hooks.ResizeBuffers->Getstdcall<HRESULT, IDXGISwapChain*, UINT, UINT, UINT, DXGI_FORMAT, UINT>();
	D3D11::ResizeBuffers(pSwapChain, BufferCount, Width, Height, NewFormat, SwapChainFlags);
	return oFun(pSwapChain, BufferCount, Width, Height, NewFormat, SwapChainFlags);
}

void Hooks::LoopbackPacketSender_sendToServer(LoopbackPacketSender* _this, uintptr_t edx, Packet* packet) {
	static auto oFunc = g_Hooks.LoopbackPacketSender_sendToServerHook->GetFastcall<void, LoopbackPacketSender*, uintptr_t, Packet*>();
	static auto noPacketMod = moduleMgr->getModule<NoPacket>();

	if (noPacketMod->isEnabled() && Game.isInGame()) return;
	bool cancelSend = false;
	moduleMgr->onSendPacket(packet, cancelSend);
	if (!cancelSend)
		oFunc(_this, edx, packet);
}

void Hooks::ClientInstanceScreenModel_sendChatMessage(void* ecx, uintptr_t edx, TextHolder* text) {
	static auto oSendMessage = g_Hooks.ClientInstanceScreenModel_sendChatMessageHook->GetFastcall<int, void*, uintptr_t, TextHolder*>();

	if (text->getTextLength() > 0) {
		char* message = text->getText();
		if (*message == cmdMgr->prefix) {
			cmdMgr->execute(message);
			return;
		}
		else if (*message == '.') {
			static bool helpedUser = false;
			if (!helpedUser) {
				helpedUser = true;
				Game.getClientInstance()->getGuiData()->displayClientMessageF(u8"%s [SimpleMod] %s >> %s 你的指令前缀是 %s ", YELLOW, WHITE, GOLD, cmdMgr->prefix);
			}
		}
	}
	oSendMessage(ecx, edx, text);
}

void Hooks::Player_tickWorldHook(Player* _this, uintptr_t edx, uintptr_t a1) {
	static auto oTick = g_Hooks.Player_tickWorld->GetFastcall<void, Player*, uintptr_t, uintptr_t>();
	if (_this != nullptr && Game.getLocalPlayer() != nullptr && _this == Game.getLocalPlayer()) {
		GameMode* gm = *reinterpret_cast<GameMode**>(reinterpret_cast<__int32>(_this) + 0x1724);
		if (_this && gm) {
			GameData::updateGameData(gm);
			moduleMgr->onWorldTick(gm);
		}
	}
	oTick(_this, edx, a1);
}

void Hooks::GameMode_startDestroyBlock(GameMode* _this, uintptr_t edx, Vec3i* pos, uint8_t face, int a4) {
	static auto oFunc = g_Hooks.GameMode_startDestroyBlockHook->GetFastcall<void, GameMode*, uintptr_t, Vec3i*, uint8_t, int>();
	static auto nukerModule = moduleMgr->getModule<Nuker>();
	if (nukerModule->isEnabled()) {
		Vec3i tempPos;
		int range = nukerModule->getNukerRadius();
		const bool isAutoMode = nukerModule->isAutoMode();
		if (!isAutoMode) {
			for (int x = -range; x < range; x++) {
				for (int y = -range; y < range; y++) {
					for (int z = -range; z < range; z++) {
						tempPos.x = pos->x + x;
						tempPos.y = pos->y + y;
						tempPos.z = pos->z + z;
						if (tempPos.y > -64) {
							_this->destroyBlock(&tempPos, face, 1);
						}
					}
				}
			}
		}
		return;	
	}
	oFunc(_this, edx, pos, face, a4);
}

__int32 _fastcall Hooks::GameMode_attack(GameMode* _this, int edx, Entity* ent) {
	static auto func = g_Hooks.GameMode_attackHook->GetFastcall<__int32, GameMode*, int, Entity*>();
	moduleMgr->onAttack(ent);
	return func(_this, edx, ent);
}

float _fastcall Hooks::GameMode_getPickRange(GameMode* _this, int edx, int a1, char a2) {
	static auto oFunc = g_Hooks.GameMode_getPickRangeHook->GetFastcall<float, GameMode*, int, int, char>();

	moduleMgr->onGetPickRange();

	if (Game.getLocalPlayer() != nullptr) {
		/*	static auto teleportModule = moduleMgr->getModule<Teleport>();
			if (teleportModule->isEnabled())
				return 255;*/

		static auto BlockReachModule = moduleMgr->getModule<BlockReach>();
		if (BlockReachModule->isEnabled())
			return BlockReachModule->getBlockReach();
	}

	return oFunc(_this, edx, a1, a2);
}

__int32 _fastcall Hooks::Actor_lerpMotion(Entity* _this, int edx, Vec3& motVec) {
	static auto oLerp = g_Hooks.Actor_lerpMotionHook->GetFastcall<__int32, Entity*, int, Vec3&>();

	if (Game.getLocalPlayer() != _this)
		return oLerp(_this, edx, motVec);

	static auto noKnockbackmod = moduleMgr->getModule<Velocity>();
	if (noKnockbackmod->isEnabled()) {
		static void* networkSender = nullptr;
		if (!networkSender)
			networkSender = reinterpret_cast<void*>(6 + FindSignature("FF 90 C0 00 00 00 C6 47 11 01 8B 4D F4 64 89 0D 00 00 00 00 59 5F 5E 5B 8B E5 5D"));

		if (networkSender == _ReturnAddress()) {
			motVec = Game.getLocalPlayer()->velocity.lerp(motVec, noKnockbackmod->xModifier, noKnockbackmod->yModifier, noKnockbackmod->xModifier);
		}
	}

	return oLerp(_this, edx, motVec);
}