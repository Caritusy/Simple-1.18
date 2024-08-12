#include "CommandRequestCommand.h"
#include "../../Module/ModuleManager.h"
#include <fstream>
#include "../../../Utils/TimerUtil.h"
CommandRequestCommand::CommandRequestCommand() :IMCCommand("Command", "Command Request", "<Command/path>") {
	registerAlias("cr");
}
CommandRequestCommand::~CommandRequestCommand() {
}
CommandRequestPacket commandrequest;
void sendToServer(std::string str) {

}
bool CommandRequestCommand::execute(std::vector<std::string>* args) {
	assertTrue(args->size() > 1);

	//auto spamMod = moduleMgr->getModule<built>();
	auto spammer = moduleMgr->getModule<Spammer>();

	if (args->at(1) == "path") {
		if (args->size() >= 2) {
			std::string directory = args->at(2);
			if (!directory.empty()) {
				spammer->getpath() = directory;
				clientMessageF(u8"%s路径设置成功!", GREEN);
				return true;
			}
		}
		else 
			throw std::exception();
	/*	std::ifstream file(directory);
		if (file.is_open()) {
			std::thread countThread([directory,ms]() {
				std::ifstream file(directory);
				std::string line;
				while (std::getline(file, line)) {
					if (line.empty())
						continue;
					if (line[0] != '/') line = "/" + line;
					commandrequest.Command.setText(line);
					Game.getClientInstance()->loopbackPacketSender->sendToServer(&commandrequest);
					std::this_thread::sleep_for(std::chrono::milliseconds(ms));
				}
				if (file.eof()) {
					Game.getClientInstance()->getGuiData()->displayClientMessageF(u8"%s导入完成.", GREEN);
				}
					file.close();
				});
			countThread.detach();
		}
		else {
			clientMessageF("%sCheck file existence or path format", RED);
			return true;
		}*/
		return true;
	}

	std::ostringstream cmd;
	for (auto is = args->begin() + 1;is != args->end();++is) {
		cmd << is->c_str();
		if (is + 1 != args->end())
			cmd << " ";
	}

	if (cmd.str()[0] != '/') cmd.str() = "/" + cmd.str();
	commandrequest.Command.setText(cmd.str());
	Game.getClientInstance()->loopbackPacketSender->sendToServer(&commandrequest);
	return true;
}