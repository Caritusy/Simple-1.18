#pragma once
#include <functional>
#include <map>
#include <mutex>
#include <queue>
#include <unordered_set>
#include "../SDK/C_EntityList.h"
#include "../SDK/ClientInstance.h"
#include "../SDK/GameMode.h"
#include "../Utils/TextFormat.h"	
#include "SlimMem.h"
struct InfoBoxData {
	bool isOpen = true;
	float fadeTarget = 1;
	float fadeVal = 0;
	float closeTimer = -1;
	std::string title;
	std::string message;

	InfoBoxData(std::string title, std::string message) : title(title), message(message) {};

	void fade() {
		fadeVal = fadeTarget - ((fadeTarget - fadeVal) * 0.65f);
		if (fadeTarget == 0 && fadeVal < 0.001f)
			isOpen = false;
	}
};

struct AABBHasher {
	size_t operator()(const AABB& i) const;
};
class GameData{
private:
	MinecraftGame* minecraftGame = nullptr;
	LocalPlayer* localPlayer = nullptr;
	ClientInstance* clientInstance = nullptr;
	uintptr_t* rendering = nullptr;
	GameMode* gameMode = nullptr;
	C_EntityList* entityList = nullptr;

	std::vector<std::string> textPrintList;
	std::mutex textPrintLock;
	std::mutex chestListMutex;
	void* hDllInst = 0;
	std::unordered_set<AABB, AABBHasher> chestList;
private:
	bool injectorConnectionActive = false;
	const SlimUtils::SlimModule* gameModule = 0;
	bool shouldTerminateB = false;
	bool shouldHideB = false;
	bool isAllowingWIPFeatures = false;
	__int32 lastUpdate;
	static void retrieveClientInstance();
	TextHolder* fakeName;
public:
	static SlimUtils::SlimMem* slimMem;
	static bool keys[0x256];
	std::queue<std::shared_ptr<InfoBoxData>> infoBoxQueue;

	static bool canUseMoveKeys();
	static bool isKeyDown(int key);
	static bool isKeyPressed(int key);
	static bool isRightClickDown();
	static bool isLeftClickDown();
	static bool isWheelDown();
	static bool shouldTerminate();
	static bool shouldHide();
	static void hide();
	static void terminate();
	static void EntityList_tick(C_EntityList* list);
	static void updateGameData(GameMode* gameMode);
	static void initGameData(const SlimUtils::SlimModule* gameModule, SlimUtils::SlimMem* slimMem, void* hDllInst);
	static void displayMessages(GuiData* guiData);
	static void log(std::string fmt, ...);

	static uintptr_t** getoPresent();
	static void CleanUpDirectX();
	inline ClientInstance* getClientInstance() { return clientInstance; };
	inline LocalPlayer* getLocalPlayer() {
		localPlayer = clientInstance->getCILocalPlayer();
		if (localPlayer == nullptr)
			gameMode = nullptr;
		return localPlayer;
	};
	LocalPlayer** getPtrLocalPlayer() {
		return &localPlayer;
	};	
	GameMode* getGameMode() { return gameMode; };
	inline GuiData* getGuiData() { return clientInstance->getGuiData(); };
	void forEachEntity(std::function<void(Entity*, bool)>);
	void forEachValidEntity(std::function<void(Entity*, bool)>);
	std::unordered_set<AABB, AABBHasher>& getChestList() { return chestList; };
	auto lockChestList() { return std::lock_guard<std::mutex>(chestListMutex); }
	void setFakeName(TextHolder* name) { fakeName = name; };
	TextHolder* getFakeName() { return fakeName; };

	inline std::shared_ptr<InfoBoxData> getFreshInfoBox() {
		while (!infoBoxQueue.empty()) {
			auto box = infoBoxQueue.front();
			if (!box->isOpen) {
				infoBoxQueue.pop();
				continue;
			}
			return box;
		}
		return std::shared_ptr<InfoBoxData>();
	}
	inline std::shared_ptr<InfoBoxData> addInfoBox(std::string title, std::string message) {
		auto box = std::make_shared<InfoBoxData>(title, message);
		infoBoxQueue.push(box);
		return box;
	}
	bool isInGame() {
		return localPlayer != nullptr;
	}
	const SlimUtils::SlimModule* getModule() {
		return gameModule;
	};
//	EntityList* getEntityList() { return entityList; };
	const SlimUtils::SlimMem* getSlimMem() {
		return slimMem;
	};



};
extern GameData Game;
