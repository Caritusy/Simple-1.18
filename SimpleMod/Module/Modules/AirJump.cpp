#include "AirJump.h"

AirJump::AirJump() :IModule('J',Category::MOVEMENT, u8"Jump even you're not on the ground. - ��������ڿ�����Ծ."){
}

AirJump::~AirJump()
{
}

std::string AirJump::getModuleName()
{
	return ("AirJump");
}

void AirJump::onTick(GameMode* gm){
	if (this->isEnabled()){
		Game.getLocalPlayer()->onGround = true;
		return;
	}	
}
