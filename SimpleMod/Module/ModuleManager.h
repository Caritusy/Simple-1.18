#pragma once
#include <typeinfo>
#include <vector>
#include <optional>
#include <memory>
#include <mutex>
#include <shared_mutex>
#include "../../Memory/GameData.h"
#include "Modules/IModule.h"
#include "../../Utils/Target.h"

#include "Modules/Fly.h"
#include "Modules/ESP.h"
#include "Modules/Bhop.h"
#include "Modules/Derp.h"
#include "Modules/Reach.h"
#include "Modules/Nuker.h"
#include "Modules/built.h"
#include "Modules/NoWeb.h"
#include "Modules/Tracer.h"
#include "Modules/GuiMod.h"
#include "Modules/Nofall.h"
#include "Modules/Hitbox.h"
#include "Modules/TpAura.h"
#include "Modules/AntiBot.h"
#include "Modules/Freecam.h"
#include "Modules/Spammer.h"
#include "Modules/AirJump.h"
#include "Modules/Crasher.h"
#include "Modules/superkb.h"
#include "Modules/NameTags.h"
#include "Modules/Scaffold.h"
#include "Modules/NoPacket.h"
#include "Modules/CPSboost.h"
#include "Modules/Killaura.h"
#include "Modules/Freelook.h"
#include "Modules/Velocity.h"
#include "Modules/Arraylist.h"
#include "Modules/HudModule.h"
#include "Modules/Criticals.h"
#include "Modules/NoFriends.h"
#include "Modules/AutoSprint.h"
#include "Modules/PacketLogs.h"
#include "Modules/BlockReach.h"
#include "Modules/FullBright.h"
#include "Modules/InstaBreak.h"
#include "Modules/InfiniteAura.h"

class ModuleManager{
private:
	GameData* gameData;
	std::vector<std::shared_ptr<IModule>> moduleList;
	bool initialized = false;
	std::shared_mutex moduleListMutex;
public:
	~ModuleManager();
	ModuleManager(GameData* gameData);

	void initModules();
	void disable();
	void onLoadConfig(void* conf);
	void onSaveConfig(void* conf);
	void onTick(GameMode* gameMode);
	void onAttack(Entity* attackedEnt);
	void onSendPacket(Packet*, bool&);
	void onWorldTick(GameMode* gameMode);
	void onKeyUpdate(int key, bool isDown);
	void onKey(int key, bool isDown, bool& shouldCancel);
	void onMove(C_MoveInputHandler* handler);
	void onPreRender();
	void onLevelRender();
	void onBaseTick(Entity*);
	void onGetPickRange();

	std::shared_lock<std::shared_mutex> lockModuleList() { return std::shared_lock(moduleListMutex); }
	std::unique_lock<std::shared_mutex> lockModuleListExclusive() { return std::unique_lock(moduleListMutex); }

	std::shared_mutex* getModuleListLock() { return &moduleListMutex; }

	bool isInitialized() { return initialized; };
	std::vector<std::shared_ptr<IModule>>* getModuleList();

	int getModuleCount();
	int getEnabledModuleCount();

	template <typename TRet>
	TRet* getModule() {
		if (!isInitialized())
			return nullptr;
		auto lock = lockModuleList();
		for (auto pMod : moduleList) {
			if (auto pRet = dynamic_cast<typename std::remove_pointer<TRet>::type*>(pMod.get())) {

				return pRet;
			}
		}
		return nullptr;
	};

	std::optional<std::shared_ptr<IModule>> getModuleByName(const std::string name) {
		if (!isInitialized())
			return nullptr;
		std::string nameCopy = name;
		std::transform(nameCopy.begin(), nameCopy.end(), nameCopy.begin(), ::tolower);

		auto lock = lockModuleList();
		for (std::vector<std::shared_ptr<IModule>>::iterator it = moduleList.begin(); it != moduleList.end(); ++it) {
			std::shared_ptr<IModule> mod = *it;
			std::string modNameCopy = mod->getRawModuleName();
			std::transform(modNameCopy.begin(), modNameCopy.end(), modNameCopy.begin(), ::tolower);
			if (modNameCopy == nameCopy)
				return std::optional<std::shared_ptr<IModule>>(mod);
		}
		return std::optional<std::shared_ptr<IModule>>();
	}

};
extern ModuleManager* moduleMgr;

