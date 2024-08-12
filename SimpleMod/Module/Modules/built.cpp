#include "built.h"

built::built() :IModule(0x0, Category::MISC, u8"导入函数包.") {
	registerFloatSetting("Delay", &delay, delay, 0, 500);
}

built::~built() {
}

std::string built::getModuleName()
{
	return ("built");
}   
static std::ifstream file;
static bool isFirstLoop = true;

void built::onTick(GameMode* gm) {
    static auto p = moduleMgr->getModule<Spammer>();
    static std::string path = p->getpath();
    if (path.empty()) {
        Game.getClientInstance()->getGuiData()->displayClientMessageF(u8"%s路径为空.", GREEN);
        setEnabled(false);
        return;
    }

    if (isFirstLoop) {
        file.open(path);
        if (!file.is_open()) {
            Game.getClientInstance()->getGuiData()->displayClientMessageF("%sCheck file existence or path format", RED);
            setEnabled(false);
            return;
        }
        isFirstLoop = false;
    }
    if (delayTime.hasTimedElapsed(delay, true)) {
        std::string line;
        if (std::getline(file, line)) {
            if (line.empty()) return;
            if (line[0] != '/') line = "/" + line;
            commandrequest.Command.setText(line);
            Game.getClientInstance()->loopbackPacketSender->sendToServer(&commandrequest);
        }
        else {
            file.close();
            Game.getClientInstance()->getGuiData()->displayClientMessageF(u8"%s导入完成.", GREEN);
            isFirstLoop = true;
            setEnabled(false);
        }
    }

}

void built::onDisable(){
    if (file.is_open()) {
        file.close();
        Game.getClientInstance()->getGuiData()->displayClientMessageF(u8"%s取消导入.", GREEN);
        isFirstLoop = true;
        setEnabled(false);
    }
}

void built::onEnable(){
    delayTime.resetTime();
}
