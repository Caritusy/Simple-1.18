#include "GameData.h"
#include <Windows.h>
#include <set>
#include "../Utils/easylogging++.h"
#include "../Utils/Utils.h"
#include "Hooks.h"
#include "../SimpleMod/DrawUtils.h"
GameData Game;
bool GameData::keys[0x256];
SlimUtils::SlimMem* GameData::slimMem;

void GameData::retrieveClientInstance() {
	static uintptr_t MinecraftGameptr = 0x0;
	if (MinecraftGameptr == 0x0) {
		MinecraftGameptr = GetOffsetFromSig("B8 ? ? ? ? 8B 4D F4 64 89 0D ? ? ? ? 59 8B E5 5D C3 68 ? ? ? ? E8 ? ? ? ? 83 C4 04 83 3D ? ? ? ? FF 75 D6 C7 45 FC ? ? ? ? E8", 1);
		LOG(INFO) << "MinecraftGameptr: " << (MinecraftGameptr ? "[OK]" : "[NO]");
	}
	Game.minecraftGame = reinterpret_cast<MinecraftGame*>(*(uintptr_t*)(MinecraftGameptr+0x1C));
	MinecraftGame* minecraftGame2 = reinterpret_cast<MinecraftGame*>(Utils::readPointer<uintptr_t*>(MinecraftGameptr, {0x1C})+0xA);
	Game.clientInstance = minecraftGame2->GetClientInstance();

#ifdef _DEBUG
	if (Game.clientInstance == 0)
		throw std::exception("Client Instance is 0");
#endif

}
#include "../SimpleMod/Hwid_user.h"
void GameData::initGameData(const SlimUtils::SlimModule* gameModule, SlimUtils::SlimMem* slimMem, void* hDllInst){

	Game.gameModule = gameModule;
	Game.slimMem = slimMem;
	Game.hDllInst = hDllInst;
	retrieveClientInstance();

	//HMODULE handler;
	//handler = GetModuleHandle("d3d11.dll");LOG(INFO)<<"d3d11.dll "<< handler<< handler ? "[OK]" : "[NO]";
	//if (handler) impl::D3D11::init();
	//handler = GetModuleHandle("opengl32.dll");LOG(INFO)<<"opengl32.dll "<<handler<<handler ? "[OK]" : "[NO]";
	//if (handler) impl::Opengl32::init();
#ifdef _DEBUG
	LOG(DEBUG)<<"Base: "<<std::hex <<Game.getModule()->ptrBase;
	if (Game.clientInstance != nullptr) {
		LOG(DEBUG)<<"ClientInstance: "<<std::hex<<Game.clientInstance;
		LOG(DEBUG) << "LocalPlayer:" << std::hex << Game.getLocalPlayer();
		LOG(DEBUG) << "minecraftGame :" << Game.minecraftGame;
	}
#else
	/*try {
		if (!Hwid_user::isTime(1718763000)) {
			Game.getClientInstance()->getGuiData()->displayClientMessageF(u8"%s时间已过期!", RED);
			Sleep(50);
			FreeLibraryAndExitThread(static_cast<HMODULE>(hDllInst), 1);
		}
		else {
			Game.getGuiData()->displayClientMessageF(u8"%s%s%s到期时间：2024-06-19 10:10:00.", GREEN, BOLD, RESET);
		}
	}
	catch (...) {
		Game.getGuiData()->displayClientMessageF(u8"%s%s%s发生了一点错误.", RED, BOLD, RESET);
		Sleep(50);
		FreeLibraryAndExitThread(static_cast<HMODULE>(hDllInst), 1);
	}*/
	return;
	try {
		if (Hwid_user::fileauth()) {
			if (!Hwid_user::isTime(Hwid_user::getexpire_time())) {
				Game.getClientInstance()->getGuiData()->displayClientMessageF(u8"%s时间已过期!", RED);
				Sleep(50);
				FreeLibraryAndExitThread(static_cast<HMODULE>(hDllInst), 1);
			}
		}
		else {
			Game.getClientInstance()->getGuiData()->displayClientMessageF(u8"%s没查询到你的用户! or 时间到期!", RED);
			Game.getClientInstance()->getGuiData()->displayClientMessageF(u8"%s[SimpleMod] >> 交流群: 320443172 & 获取验证|反馈 Developer-QwQ@outlook.com", RED);
			//LOG(INFO) << "如果你有了Auth你就创建一个文件放在目录然后将神秘代码复制进去并且将文件命名为Auth没有后缀";
			LOG(INFO) << "Hwid: "<< Hwid_user::GetHwid().c_str();
			Sleep(50);
			FreeLibraryAndExitThread(static_cast<HMODULE>(hDllInst), 1);
		}
	}
	catch (...) {
		Game.getGuiData()->displayClientMessageF(u8"%s%s%s发生了一点错误.", RED, BOLD, RESET);
		Sleep(50);
		FreeLibraryAndExitThread(static_cast<HMODULE>(hDllInst), 1);
	}
#endif
}




bool GameData::canUseMoveKeys(){
	if (Game.minecraftGame == nullptr) {
		return false;
	}
	return Game.minecraftGame->canUseKeybinds();
}

bool GameData::isKeyDown(int key){
	return keys[(int)key];
}

bool GameData::isKeyPressed(int key){
	if (isKeyDown(key)) {
		while (isKeyDown(key))
			Sleep(1);
		return true;
	}
	return false;
}

bool GameData::isRightClickDown()
{
	return false;
}

bool GameData::isLeftClickDown()
{
	return false;
}

bool GameData::isWheelDown()
{
	return false;
}

bool GameData::shouldTerminate()
{
	return false;
}

bool GameData::shouldHide()
{
	return false;
}

void GameData::hide()
{
}

void GameData::terminate()
{
}

void GameData::EntityList_tick(C_EntityList* list){
	Game.entityList = list;
}

void GameData::updateGameData(GameMode* gameMode){
	retrieveClientInstance();
	Game.localPlayer = Game.getLocalPlayer();

	if (Game.localPlayer != nullptr) {
		Game.gameMode = gameMode;
		QueryPerformanceCounter(reinterpret_cast<LARGE_INTEGER*>(&Game.lastUpdate));

		if (Game.localPlayer != nullptr) {
			GuiData* guiData = Game.clientInstance->getGuiData();
			if (guiData != nullptr) {
				displayMessages(guiData);
			}
		}
	}
}
void GameData::displayMessages(GuiData* guiData) {


}
void GameData::log(std::string fmt, ...){
	va_list arg;
	va_start(arg, fmt);
	char message[300];
	vsprintf_s(message, fmt.c_str(), arg);
	va_end(arg);
	std::unique_lock<std::mutex> lock(Game.textPrintLock);
	Game.textPrintList.emplace_back(message);
}
IDXGISwapChain* pSwapChain;
ID3D11Device* pDevice = nullptr;
ID3D11DeviceContext* pContext = nullptr;
uintptr_t** GameData::getoPresent(){

	WNDCLASSEXA wc = { sizeof(WNDCLASSEX), CS_CLASSDC, DefWindowProc, 0L, 0L, GetModuleHandleA(NULL), NULL, NULL, NULL, NULL, "DX", NULL };
	RegisterClassExA(&wc);
	HWND hWnd = CreateWindowA("DX", NULL, WS_OVERLAPPEDWINDOW, 100, 100, 300, 300, NULL, NULL, wc.hInstance, NULL);
	D3D_FEATURE_LEVEL requestedLevels[] = { D3D_FEATURE_LEVEL_11_0, D3D_FEATURE_LEVEL_10_1 };
	D3D_FEATURE_LEVEL obtainedLevel;
	DXGI_SWAP_CHAIN_DESC scd;
	ZeroMemory(&scd, sizeof(scd));
	scd.BufferCount = 1;
	scd.BufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
	scd.BufferDesc.Scaling = DXGI_MODE_SCALING_UNSPECIFIED;
	scd.BufferDesc.ScanlineOrdering = DXGI_MODE_SCANLINE_ORDER_UNSPECIFIED;
	scd.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
	scd.Flags = DXGI_SWAP_CHAIN_FLAG_ALLOW_MODE_SWITCH;
	scd.OutputWindow = hWnd;
	scd.SampleDesc.Count = 1;
	scd.SwapEffect = DXGI_SWAP_EFFECT_DISCARD;
	scd.Windowed = ((GetWindowLongPtr(hWnd, GWL_STYLE) & WS_POPUP) != 0) ? false : true;
	scd.BufferDesc.Width = 1;
	scd.BufferDesc.Height = 1;
	scd.BufferDesc.RefreshRate.Numerator = 0;
	scd.BufferDesc.RefreshRate.Denominator = 1;
	if (FAILED(D3D11CreateDeviceAndSwapChain(nullptr,D3D_DRIVER_TYPE_HARDWARE,nullptr,0,
		requestedLevels,sizeof(requestedLevels) / sizeof(D3D_FEATURE_LEVEL),
		D3D11_SDK_VERSION,&scd,&pSwapChain,&pDevice,&obtainedLevel,&pContext)))
	{
		LOG(DEBUG) << "Failed to create directX device and swapchain! [Error]";
		return nullptr;
	}
	return (uintptr_t**)pSwapChain;
}
void GameData::CleanUpDirectX(){
	if (pContext) {
		pContext->Release();
		pContext = nullptr;
	}
	if (pDevice) {
		pDevice->Release();
		pDevice = nullptr;
	}
	if (pSwapChain) {
		pSwapChain->Release();
		pSwapChain = nullptr;
	}
}
void GameData::forEachEntity(std::function<void(Entity*, bool)>callback) {

	if (this->localPlayer) {
		for (const auto& ent : g_Hooks.entityList){
		
			[ent, &callback]() {
				__try {
					if (ent.ent != nullptr) [[likely]] {
						ent.ent->GetNameTag(); //chect ent will crash
					
						callback(ent.ent, false);
					}
				}
				__except (EXCEPTION_EXECUTE_HANDLER) {
				}
			}();
		}
		//for (const auto ent : Game.getLocalPlayer()->level->getMiscEntityList())
		//{
		//	[ent, &callback]() {
		//		__try {
		//			if (ent != nullptr && ent->getEntityTypeId() >= 1 && ent->getEntityTypeId() <= 999999999) [[likely]] {
		//				ent->getNameTag(); //chect ent will crash
		//				callback(ent, false);
		//			}
		//		}
		//		__except (EXCEPTION_EXECUTE_HANDLER) {
		//		}
		//	}();
		//}
	}
}
void GameData::forEachValidEntity(std::function<void(Entity*, bool)> callback){
	if (localPlayer && localPlayer->level) {
		for (const auto ent : g_Hooks.entityList)
		{
			[ent, &callback]() {
				__try {
					if (ent.ent != nullptr) [[likely]] {
						ent.ent->GetNameTag(); //chect ent will crash
						callback(ent.ent, false);
					}
				}
				__except (EXCEPTION_EXECUTE_HANDLER) {
				}
			}();
		}
	}
}