#include "IMCCommand.h"

void IMCCommand::registerAlias(const char* str){
	std::string ss = str;
	std::transform(ss.begin(), ss.end(), ss.begin(), ::tolower);
	aliasList.push_back(ss);
}

void IMCCommand::clientMessageF(const char* fmt, ...){
	va_list arg;
	va_start(arg, fmt);
	Game.getGuiData()->displayClientMessageVA(fmt, arg);
	va_end(arg);
}

IMCCommand::IMCCommand(const char* command, const char* description, const char* usage){
	_command = command;
	_description = description;
	_usage = usage;
	registerAlias(command);
}

IMCCommand::~IMCCommand()
{
}

bool IMCCommand::execute(std::vector<std::string>* args)
{
    return false;
}
