#include "NoPacket.h"

NoPacket::NoPacket():IModule(0x0,Category::MISC,u8"Prevents you from sending InventoryTransaction packets. - Í£Ö¹Êý¾Ý°ü."){
}

NoPacket::~NoPacket(){
}

std::string NoPacket::getModuleName()
{
	return "NoPacket";
}
