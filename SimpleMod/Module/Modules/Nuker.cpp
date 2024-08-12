#include "Nuker.h"
Nuker::Nuker() :IModule('N', Category::WORLD, u8"Break multiple blocks at once. - 你可以范围性的破坏你周围的块.") {
	registerIntSetting("nukerRadius",&nukerRadius,nukerRadius,1,8);
}

Nuker::~Nuker()
{
}

std::string Nuker::getModuleName()
{
	return ("Nuker");
}

void Nuker::onTick(GameMode* gm){
	if (!autodestroy) return;
	for (int x = -nukerRadius; x < nukerRadius; x++) {
		for (int y = -1; y < nukerRadius; y++) {
			for (int z = -nukerRadius; z < nukerRadius; z++) {
				tempPos.x = (int)Game.getLocalPlayer()->getPos()->x + x;
				tempPos.y = (int)Game.getLocalPlayer()->getPos()->y + y;
				tempPos.z = (int)Game.getLocalPlayer()->getPos()->z + z;
				if (tempPos.y > -64) {
					gm->destroyBlock(&tempPos,1,1);
				}
			}
		}
	}
}
