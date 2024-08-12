#include "Target.h"
#include <regex>
#include "../SimpleMod/Module/ModuleManager.h"
#include "../Memory/Hooks.h"


LocalPlayer** localPlayer;
bool Target::containsOnlyASCII(const std::string& string){
	for (auto c : string) {
		int n = static_cast<unsigned char>(c);
		if (n > 127 && n != -89) {
			return false;
		}
	}
	return true;
}

void Target::init(LocalPlayer** cl){
	localPlayer = cl;
}

bool Target::isValidTarget(Entity* ent){
	static auto noFriendsMod = moduleMgr->getModule<NoFriends>();
	static auto antibotMod = moduleMgr->getModule<AntiBot>();
	static auto hitboxMod = moduleMgr->getModule<Hitbox>();

	auto localPlayer = Game.getLocalPlayer();
	if (ent == nullptr)
		return false;

	if (ent == localPlayer)
		return false;

	if (!ent->isAlive())
		return false;
	auto entityTypeId = ent->getEntityTypeId();
	if (antibotMod->isEnabled()) {
		if (antibotMod->hitboxCheck) {
			if (hitboxMod->isEnabled()) {
				if (ent->height > hitboxMod->height || ent->width > hitboxMod->width)
					return false;
			}
			else {
				if (ent->height > 1.8f)
					return false;

				if (ent->height < 1.79f && ent->height > 0.65f)
					return false;

				if (ent->height < 1.649f && ent->height > 0.6f)
					return false;

				if (ent->width > 0.6f || ent->width < 0.59f)
					return false;
			}
			if (antibotMod->nameCheck) {
				std::string targetName = ent->GetNameTag()->getText();
				if (ent->GetNameTag()->getTextLength() < 1)
					return false;

				if (localPlayer->canShowNameTag() && !ent->canShowNameTag())
					return false;

				if (localPlayer->checkNameTagFunc() && !ent->checkNameTagFunc())
					return false;
				if ((std::string(localPlayer->GetNameTag()->getText()).find(std::string("\n")) == std::string::npos) && (targetName.find(std::string("\n")) != std::string::npos))
					return false;
			}
			/*if (antibotMod->invisibleCheck) {
				if (ent->isInvisible())
					return false;
			}*/
			if (antibotMod->entityIdCheck) {
				if (entityTypeId != 319)
					return false;
			}
			/*if (antibotMod->moveCheck) {
				if (ent->isSilent())
					return false;

				if (ent->isImmobile())
					return false;
			}*/
			if (antibotMod->modeCheck) {
				if (ent->gamemode == 1)
					return false; //不攻击创造模式的玩家
			}
			if (antibotMod->Serverbots) {
				if ((ent->yaw == 0.f || ent->pitch == 0.f) && [ent]()->bool {
						for (size_t i = 0;i != ent->GetNameTag()->textLength;i++) {
							if (ent->GetNameTag()->getText()[i] == '@') return true;}
						}()) return false;
				
			}
		}

	}

	/*if (!noFriendsMod->isEnabled())
		return false;*/

	return true;
}
