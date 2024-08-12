#include "AutoSprint.h"

AutoSprint::AutoSprint() : IModule(0, Category::MOVEMENT, "Automatically sprint without holding the key.") {
	registerBoolSetting("All Directions", &alldirections, alldirections);
}

AutoSprint::~AutoSprint() {
}

std::string AutoSprint::getModuleName() {
	return ("AutoSprint");
}

//void AutoSprint::onTick(GameMode* gm) {
//	if (Game.getLocalPlayer()->velocity.magnitudexz() > 0.05f) {
//		if (alldirections || GameData::isKeyDown('W'))
//			Game.getLocalPlayer()->setSprinting(true);
//	}
//}

void AutoSprint::onMove(C_MoveInputHandler* input){
if (Game.getLocalPlayer()->velocity.magnitudexz() > 0.05f && !input->isSprintkey) {
	if (alldirections || GameData::isKeyDown('W'))
		Game.getLocalPlayer()->setSprinting(true);
}
}
