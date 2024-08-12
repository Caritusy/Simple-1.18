#include "ModulesCommand.h"
#include <algorithm>
#include "../../Module/ModuleManager.h"
ModulesCommand::ModulesCommand() : IMCCommand("modules", "Lists all modules", ""){
    registerAlias("mods");
}

ModulesCommand::~ModulesCommand()
{
}

bool ModulesCommand::execute(std::vector<std::string>* args)
{
	auto lock = moduleMgr->lockModuleList();
	std::vector<std::shared_ptr<IModule>>* modules = moduleMgr->getModuleList();
	clientMessageF("=====================================");
	clientMessageF("Modules (%i):", modules->size());
	for (auto& mod : *modules) {
		clientMessageF("%s[SimpleMod]%s >> %s %s- %s%s", GOLD, WHITE, mod->getModuleName().c_str(), GRAY, ITALIC, mod->getTooltip());
	}
	return true;
}
