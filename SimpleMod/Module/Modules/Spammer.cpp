#include "Spammer.h"
Spammer::Spammer():IModule(0x0,Category::MISC, "Spams a message in a specified delay."){
	registerBoolSetting("Import", &Import, Import);
	registerFloatSetting("Delay", &delay, delay, 0, 1500);
	registerIntSetting("Length", &length, length, 0, 80);
	registerBoolSetting("Bypass", &bypass, bypass);

//	registerTextSetting("message", &message);
}

Spammer::~Spammer()
{
}



void Spammer::onEnable()
{
	if (Game.getLocalPlayer() == nullptr)
		setEnabled(false);
	delayTime.resetTime();
}

std::string Spammer::getModuleName()
{
    return ("Spammer");
}
static std::ifstream file;
static bool isFirstLoop = true;
void Spammer::onTick(GameMode* gm){
//	static auto p = moduleMgr->getModule<built>();

	if (Game.getLocalPlayer() == nullptr)
		return;
	if (!Game.getLocalPlayer()->checkNameTagFunc())
		return;
	if (Import) {

		if (path.empty()) {
			Game.getClientInstance()->getGuiData()->displayClientMessageF(u8"%s路径为空.请使用.Command设置路径", GREEN);
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
				if (line[0] == '/') {
					Game.getClientInstance()->getGuiData()->displayClientMessageF(u8"%s检查文件是否是不是命令文件！", RED);
					setEnabled(false);
					return;
				}
				textPacket.messageType = 1;
				textPacket.message.setText(line);
				textPacket.sourceName.setText(Game.getLocalPlayer()->GetNameTag()->getText());
				Game.getClientInstance()->loopbackPacketSender->sendToServer(&textPacket);
			}
			else {
				file.close();
				Game.getClientInstance()->getGuiData()->displayClientMessageF(u8"%s导入完成.", GREEN);
				isFirstLoop = true;
				setEnabled(false);
			}
		}
	
	}
	else if (delayTime.hasTimedElapsed(delay, true)) {
		textPacket.messageType = 1;
		textPacket.message.setText(bypass ? ( message + " | " + Utils::randomString(length)) : message);
		textPacket.sourceName.setText(Game.getLocalPlayer()->GetNameTag()->getText());
		Game.getClientInstance()->loopbackPacketSender->sendToServer(&textPacket);
	}
}
void Spammer::onDisable() {
	file.close();
	Game.getClientInstance()->getGuiData()->displayClientMessageF(u8"%s取消导入.", GREEN);
	isFirstLoop = true;
}