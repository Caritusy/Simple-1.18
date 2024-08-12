#include "InstaBreak.h"
InstaBreak::InstaBreak() : IModule(VK_NUMPAD4, Category::WORLD, "Break any block instantly.") {
	/*mode = SettingEnum(this)
		.addEntry(EnumEntry("Destroy", 0))
		.addEntry(EnumEntry("FastDig", 1))
		.addEntry(EnumEntry("The Hive", 2));
	registerEnumSetting("Mode", &mode, 0);*/
}


InstaBreak::~InstaBreak()
{
}

std::string InstaBreak::getModuleName()
{
	return ("InstaBreak");
}

void InstaBreak::onTick(GameMode* gm){
	Level* level = Game.getLocalPlayer()->level;
	if (!GameData::canUseMoveKeys() && !(GetAsyncKeyState(VK_LBUTTON) & 0x01)) {
		tick = 0;
		return;
	}
	else {
		if (level->rayHitType != 0)
			return; //是否有指向方块

		++tick;
		if (tick >= 10) {
			tick = 0;
		}
		else if (tick == 1) {

			actionPacket.entityRuntimeId = Game.getLocalPlayer()->EntityRuntimeid;
			actionPacket.face = level->blockSide;
			actionPacket.blockPosition = Vec3i(level->block);

			actionPacket.action = 0; //开始破坏
			Game.getClientInstance()->loopbackPacketSender->sendToServer(&actionPacket);

			actionPacket.action = 18; //继续破坏
			for (int i = 0; i < 10; i++) {
				Game.getClientInstance()->loopbackPacketSender->sendToServer(&actionPacket);
			}
			//	//printf("x[%d]y[%d]z[%d] blockSide %d", Vec3i(level->block).x, Vec3i(level->block).y, Vec3i(level->block).z, level->blockSide);
				//Game.getClientInstance()->getGuiData()->displayClientMessageF("x[%d]y[%d]z[%d] blockSide %d", Vec3i(level->block).x, Vec3i(level->block).y, Vec3i(level->block).z,level->blockSide);

			gm->destroyBlock(&Vec3i(level->block), level->blockSide, true);

			actionPacket.action = 2; //停止破坏
			Game.getClientInstance()->loopbackPacketSender->sendToServer(&actionPacket);
		}
	
	}

	
}
