#include "PlaysoundCommand.h"
#include "../../Module/ModuleManager.h"

PlaysoundCommand::PlaysoundCommand() :IMCCommand("playsound","Play a sound effect.","<Music ID/rowdy><number>"){
}

PlaysoundCommand::~PlaysoundCommand()
{
}

bool PlaysoundCommand::execute(std::vector<std::string>* args){
	assertTrue(Game.getLocalPlayer() != nullptr);
	assertTrue(args->size() > 1);
	if (args->size() > 2) {
		if (args->at(1) == "rowdy") {
			for (int i = 0;i < assertInt(args->at(2));i++) {
				static LevelSoundEventPacket playsound;
				playsound.sound = i;
				playsound.pos = *Game.getLocalPlayer()->getPos();
				Game.getClientInstance()->loopbackPacketSender->sendToServer(&playsound);
			}
		}
		else {
			for (int i = 0;i < assertInt(args->at(2));i++) {
				static LevelSoundEventPacket playsound;
				playsound.sound = assertInt(args->at(1));
				playsound.pos = *Game.getLocalPlayer()->getPos();
				Game.getClientInstance()->loopbackPacketSender->sendToServer(&playsound);
			}
		}
		return true;
	}
	static LevelSoundEventPacket playsound;
	playsound.sound = assertInt(args->at(1));
	playsound.pos = *Game.getLocalPlayer()->getPos();
	Game.getClientInstance()->loopbackPacketSender->sendToServer(&playsound);
	return true;
}
