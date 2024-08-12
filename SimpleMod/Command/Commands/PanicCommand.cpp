#include "PanicCommand.h"
#include <algorithm>
#include "../../Module/ModuleManager.h"
PanicCommand::PanicCommand(): IMCCommand("panic", "Disables all Modules", ""){
}

PanicCommand::~PanicCommand()
{
}

bool PanicCommand::execute(std::vector<std::string>* args){
	auto lock = moduleMgr->lockModuleList();
	std::vector<std::shared_ptr<IModule>>* modules = moduleMgr->getModuleList();
	for (auto& mod : *modules) {
		mod->setEnabled(false);
	}
	clientMessageF("[%sSimpleMod%s] %sDisabled all Modules!", GOLD, WHITE, GREEN);
	return true;
}
