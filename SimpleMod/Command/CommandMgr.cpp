#include "CommandMgr.h"

#include "../Module/ModuleManager.h"

#include "Commands/UserCommand.h"
#include "Commands/HelpCommand.h"
#include "Commands/TestCommand.h"
#include "Commands/BindCommand.h"
#include "Commands/ConfigCommand.h"
#include "Commands/SpammerCommand.h"
#include "Commands/TeleportCommand.h"
#include "Commands/GameModeCommand.h"
#include "Commands/playsoundCommand.h"
#include "Commands/CommandRequestCommand.h"

CommandMgr::CommandMgr(GameData* gm) {
	gameData = gm;
}

CommandMgr::~CommandMgr() {
	for (int i = 0; i < commandList.size(); i++) {
		delete commandList[i];
		commandList[i] = nullptr;
	}
}

void CommandMgr::initCommands() {
	LOG(INFO) << "Initializing commands";
	commandList.push_back(new HelpCommand());
	commandList.push_back(new BindCommand());
	commandList.push_back(new UserCommand());
	commandList.push_back(new ConfigCommand());
	//	commandList.push_back(new SpammerCommand());
	commandList.push_back(new GameModeCommand());
	commandList.push_back(new TeleportCommand());
	commandList.push_back(new PlaysoundCommand());

	commandList.push_back(new CommandRequestCommand());

#ifdef _DEBUG
	commandList.push_back(new TestCommand());
#endif
}

void CommandMgr::disable()
{
}

std::vector<IMCCommand*>* CommandMgr::getCommandList() {
	return &commandList;
}

void CommandMgr::execute(char* message) {
	if (message == nullptr) return;
	std::vector<std::string> args;
	std::string msgStr = message + 1;
	size_t pos = msgStr.find(" "), initialPos = 0;
	while (pos != std::string::npos) {
		args.push_back(msgStr.substr(initialPos, pos - initialPos));
		initialPos = pos + 1;
		pos = msgStr.find(" ", initialPos);
	}
	args.push_back(msgStr.substr(initialPos, (std::min)(pos, msgStr.size()) - initialPos + 1));

	std::string cmd = args[0];
	std::transform(cmd.begin(), cmd.end(), cmd.begin(), ::tolower);
	auto modOpt = moduleMgr->getModuleByName(args[0]);
	if (modOpt.has_value()) {
		auto mod = modOpt.value();
		std::vector<std::shared_ptr<IModule>>* modules = moduleMgr->getModuleList();
		try {
			if (args.size() - 1 >= 1) {
				std::ostringstream os;
				for (auto it = modules->begin(); it != modules->end(); ++it) {
					auto setting = mod->getSettings();
					if (args.at(1) == "?" || args.at(1) == "help") {
						for (auto is = setting->begin();is != setting->end();++is) {
							auto settings = *is;
							if (strcmp(settings->name, "enabled") == 0 || strcmp(settings->name, "keybind") == 0)
								continue;
							if (settings->valueType == ValueType::ENUM_T) continue;
							os << settings->name;
							if (is + 1 != setting->end())
								os << "/";
						}
						Game.getGuiData()->displayClientMessageF(u8"%s%sUsage: %s%c<%s> <%s>", RED, BOLD, RESET, cmdMgr->prefix, mod->getModuleName().c_str(), os.str().c_str());
						return;
					}
					else
						if (setting->size() - 2 <= 0) {
							Game.getGuiData()->displayClientMessageF(u8"%s%sUsage: %s%c<Module> <none>", RED, BOLD, RESET, cmdMgr->prefix);
							return;
						}
					if (args.size() - 1 <= setting->size() - 2) {
						int e = 1;
						for (auto is = setting->begin();is != setting->end();++is) {
							auto settings = *is;
							if (strcmp(settings->name, "enabled") == 0 || strcmp(settings->name, "keybind") == 0)continue;
							if (settings->valueType == ValueType::ENUM_T) continue;
							if (settings->valueType == ValueType::INT_T) {
								if (std::stoi(args.at(e)) < settings->minValue->_int || std::stoi(args.at(e)) > settings->maxValue->_int) {
									Game.getGuiData()->displayClientMessageF("%s%s [min %i][max %i]", RED, settings->name, settings->minValue->_int, settings->maxValue->_int);
								}
								else {
									if (args.at(e) == "~") {
										Game.getGuiData()->displayClientMessageF("%s%s %s[%f]", GREEN, mod->getModuleName().c_str(), settings->name, std::stof(args.at(e)));
										continue;
									}
									else {
										settings->value->_int = std::stoi(args.at(e));
										Game.getGuiData()->displayClientMessageF(u8"%s%s %s[%i]", GREEN, mod->getModuleName().c_str(), settings->name, std::stoi(args.at(e)));
									}
								}
							}
							else if (settings->valueType == ValueType::FLOAT_T) {
								if (std::stof(args.at(e)) < settings->minValue->_float || std::stof(args.at(e)) > settings->maxValue->_float) {
									Game.getGuiData()->displayClientMessageF("%s%s [min %f][max %f]", RED, settings->name, settings->minValue->_float, settings->maxValue->_float);
								}
								else {
									if (args.at(e) == "~") {
										Game.getGuiData()->displayClientMessageF("%s%s %s[%f]", GREEN, mod->getModuleName().c_str(), settings->name, std::stof(args.at(e)));
										continue;
									}
									else {
										settings->value->_float = std::stof(args.at(e));
										Game.getGuiData()->displayClientMessageF("%s%s %s[%f]", GREEN, mod->getModuleName().c_str(), settings->name, std::stof(args.at(e)));
									}
								}
							}
							else if (settings->valueType == ValueType::BOOL_T) {
								std::string option = args.at(e);
								std::transform(option.begin(), option.end(), option.begin(), ::tolower);
								if (option != "true" && option != "false") {
									Game.getGuiData()->displayClientMessageF("%s%s <true/false>", RED, settings->name);
									return;
								}
								else {
									if (args.at(e) == "~") {
										Game.getGuiData()->displayClientMessageF("%s%s %s[%f]", GREEN, mod->getModuleName().c_str(), settings->name, std::stof(args.at(e)));
										continue;
									}
									else {
										settings->value->_bool = option == "true";
										Game.getGuiData()->displayClientMessageF("%s%s %s[%s]", settings->value->_bool ? GREEN : RED, mod->getModuleName().c_str(), settings->name, args.at(e).c_str());
									}
								}
							}
							else if (settings->valueType == ValueType::TEXT_T) {
								if (args.at(e) == "~") {
									Game.getGuiData()->displayClientMessageF("%s%s %s[%f]", GREEN, mod->getModuleName().c_str(), settings->name, std::stof(args.at(e)));
									continue;
								}
								*settings->value->text = args.at(e);
								Game.getGuiData()->displayClientMessageF("%s%s %s[%s]", GREEN, mod->getModuleName().c_str(), settings->name, args.at(e).c_str());
							}
							e++;if (e >= args.size()) return;
						}
					}
				}
				return;
			}
			else {
				mod->toggle();
				Game.getGuiData()->displayClientMessageF("[%sSimpleMod%s] >> %s%s %s!", GOLD, WHITE, mod->isEnabled() ? GREEN : RED, mod->getModuleName().c_str(), mod->isEnabled() ? u8"enabled ✓" : u8"disabled ✕");
				return;
			}
			return;
		}
		catch (...) {
			Game.getGuiData()->displayClientMessageF("%s%sUsage: %s%c<Module> <help>", RED, BOLD, RESET, cmdMgr->prefix);
			return;
		}
	}

	for (auto& c : commandList) {
		auto aliases = c->getAliasList();
		for (const auto& alias : *aliases) {
			if (alias == cmd) {
				try {
					if (!c->execute(&args)) {
						Game.getGuiData()->displayClientMessageF("%s%sUsage: %s%c%s %s", RED, BOLD, RESET, cmdMgr->prefix, c->getCommand(), c->getUsage(cmd.c_str()));
					}
				}
				catch (...) {
					Game.getGuiData()->displayClientMessageF("%s%sUsage: %s%c%s %s", RED, BOLD, RESET, cmdMgr->prefix, c->getCommand(), c->getUsage(cmd.c_str()));
				}
				return;
			}
		}
	}
	Game.getGuiData()->displayClientMessageF("[%sSimpleMod%s] %sCommand '%s ' could not be found!", GOLD, WHITE, RED, cmd.c_str());
	for (auto it = this->commandList.begin(); it != this->commandList.end(); ++it) {
		IMCCommand* c = *it;
		std::string commandCopy = c->getCommand();
		std::transform(commandCopy.begin(), commandCopy.end(), commandCopy.begin(), ::tolower);
		std::transform(cmd.begin(), cmd.end(), cmd.begin(), ::tolower);
		if (commandCopy.find(cmd) != std::string::npos)                                                 // if it has the name in it but not completed
			Game.getGuiData()->displayClientMessageF("%sDid you mean to type: %s?", RED, commandCopy.c_str());  // Tell the user what they might have ment
	}
}
CommandMgr* cmdMgr = new CommandMgr(&Game);