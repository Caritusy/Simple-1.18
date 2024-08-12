#include "ModuleManager.h"
#include "../../Utils/easylogging++.h"
#include "../../Utils/Json.hpp"

using json = nlohmann::json;
ModuleManager::~ModuleManager(){
	initialized = false;
	auto lock = lockModuleListExclusive();
	moduleList.clear();
}

ModuleManager::ModuleManager(GameData* gameData){
	gameData = gameData;
}

void ModuleManager::initModules(){
	LOG(INFO) << "Initializing modules.";
	{
		auto lock = lockModuleListExclusive();
		moduleList.push_back(std::shared_ptr<IModule>(new Fly()));
		moduleList.push_back(std::shared_ptr<IModule>(new ESP()));
		moduleList.push_back(std::shared_ptr<IModule>(new Bhop()));
		moduleList.push_back(std::shared_ptr<IModule>(new Derp()));
		moduleList.push_back(std::shared_ptr<IModule>(new Reach()));
		moduleList.push_back(std::shared_ptr<IModule>(new NoWeb()));
		moduleList.push_back(std::shared_ptr<IModule>(new Nuker()));
		moduleList.push_back(std::shared_ptr<IModule>(new NoFall()));
		moduleList.push_back(std::shared_ptr<IModule>(new Tracer()));
		moduleList.push_back(std::shared_ptr<IModule>(new TpAura()));
		moduleList.push_back(std::shared_ptr<IModule>(new Hitbox()));
		moduleList.push_back(std::shared_ptr<IModule>(new Crasher()));
		moduleList.push_back(std::shared_ptr<IModule>(new AntiBot()));
		moduleList.push_back(std::shared_ptr<IModule>(new Spammer()));
		moduleList.push_back(std::shared_ptr<IModule>(new Freecam()));
		moduleList.push_back(std::shared_ptr<IModule>(new AirJump()));
		moduleList.push_back(std::shared_ptr<IModule>(new superkb()));
		moduleList.push_back(std::shared_ptr<IModule>(new Velocity()));
		moduleList.push_back(std::shared_ptr<IModule>(new NoPacket()));
		moduleList.push_back(std::shared_ptr<IModule>(new Scaffold()));
		moduleList.push_back(std::shared_ptr<IModule>(new Killaura()));
		moduleList.push_back(std::shared_ptr<IModule>(new NameTags()));
		moduleList.push_back(std::shared_ptr<IModule>(new Freelook()));
		moduleList.push_back(std::shared_ptr<IModule>(new CPSboost()));
	//	moduleList.push_back(std::shared_ptr<IModule>(new Arraylist()));
		moduleList.push_back(std::shared_ptr<IModule>(new Criticals()));
		moduleList.push_back(std::shared_ptr<IModule>(new NoFriends()));
		moduleList.push_back(std::shared_ptr<IModule>(new HudModule()));
		moduleList.push_back(std::shared_ptr<IModule>(new BlockReach()));
		moduleList.push_back(std::shared_ptr<IModule>(new AutoSprint()));
	//	moduleList.push_back(std::shared_ptr<IModule>(new InstaBreak()));
		moduleList.push_back(std::shared_ptr<IModule>(new FullBright()));
		moduleList.push_back(std::shared_ptr<IModule>(new ClickGuiMod()));
		moduleList.push_back(std::shared_ptr<IModule>(new InfiniteAura()));
	//	moduleList.push_back(std::shared_ptr<IModule>(new built()));


		std::sort(moduleList.begin(), moduleList.end(), [](auto lhs, auto rhs) {
			auto current = lhs;
			auto other = rhs;
			return std::string{*current->getModuleName().c_str()} < std::string{*other->getModuleName().c_str()};
			});
		initialized = true;
	}
#ifdef _DEBUG
	moduleList.push_back(std::shared_ptr<IModule>(new PacketLogs()));
#endif // _DEBUG

}

void ModuleManager::disable(){
	auto lock = lockModuleList();
	for (auto& mod : moduleList) {
		if (mod->isEnabled())
			mod->setEnabled(false);
	}
}

void ModuleManager::onLoadConfig(void* confVoid){
	auto conf = reinterpret_cast<json*>(confVoid);
	if (!isInitialized())
		return;
	auto lock = lockModuleList();
	for (auto& mod : moduleList) {
		mod->onLoadConfig(conf);
	}
}

void ModuleManager::onSaveConfig(void* confVoid){
	auto conf = reinterpret_cast<json*>(confVoid);
	if (!isInitialized())
		return;
	auto lock = lockModuleList();
	for (auto& mod : moduleList) {
		mod->onSaveConfig(conf);
	}
}

void ModuleManager::onTick(GameMode* gameMode){
	if (!isInitialized())
		return;
	auto lock = lockModuleList();
	for (auto& mod : moduleList) {
		if (mod->isEnabled())
			mod->onTick(gameMode);
	}
}

void ModuleManager::onAttack(Entity* attackEnt){
	if (!isInitialized())
		return;
	auto lock = lockModuleList();
	for (auto& mod : moduleList) {
		if (mod->isEnabled())
			mod->onAttack(attackEnt);
	}
}

void ModuleManager::onSendPacket(Packet* packet,bool& cancelSend){
	if (!isInitialized())
		return;
	auto lock = lockModuleList();
	for (auto& it : moduleList) {
		if (it->isEnabled())
			it->onSendPacket(packet, cancelSend);
	}
}

void ModuleManager::onWorldTick(GameMode* gameMode){
	if (!isInitialized())
		return;
	auto lock = lockModuleList();
	for (auto& mod : moduleList) {
		if (mod->isEnabled())
			mod->onWorldTick(gameMode);
	}
}

void ModuleManager::onKeyUpdate(int key, bool isDown){
	if (!isInitialized())
		return;
	auto lock = lockModuleList();
	for (auto& mod : moduleList) {
		mod->onKeyUpdate(key, isDown);
	}
}

void ModuleManager::onKey(int key, bool isDown, bool& shouldCancel){
	if (!isInitialized())
		return;
	auto mutex = lockModuleList();

	for (auto& mod : moduleList) {
		if (mod->isEnabled())
			mod->onKey(key, isDown, shouldCancel);
	}
}

void ModuleManager::onMove(C_MoveInputHandler* handler){
	if (!isInitialized())
		return;
	auto lock = lockModuleList();
	for (auto& it : moduleList) {
		if (it->isEnabled())
			it->onMove(handler);
	}
}

void ModuleManager::onPreRender(){
	if (!isInitialized())
		return;
	auto lock = lockModuleList();
	for (auto& it : moduleList) {
		if (it->isEnabled())
			it->onPreRender();
	}
}

void ModuleManager::onLevelRender()
{
}

void ModuleManager::onBaseTick(Entity* ent){
	if (!isInitialized())
		return;
	auto lock = lockModuleList();
	for (auto& mod : moduleList) {
		mod->onBaseTick(ent);
	}
}

void ModuleManager::onGetPickRange(){
if (!isInitialized())
return;
auto lock = lockModuleList();
for (auto& it : moduleList) {
	if (it->isEnabled())
		it->onGetPickRange();
}
}

std::vector<std::shared_ptr<IModule>>* ModuleManager::getModuleList(){
	return &moduleList;
}

int ModuleManager::getModuleCount()
{
	return (int)moduleList.size();
}

int ModuleManager::getEnabledModuleCount(){
	int i = 0;
	auto lock = lockModuleList();
	for (auto& it : moduleList) {
		if (it->isEnabled()) i++;
	}
	return i;
}

ModuleManager* moduleMgr = new ModuleManager(&Game);