#include "NoPacket.h"

NoPacket::NoPacket():IModule(0x0,Category::MISC,u8"Prevents you from sending InventoryTransaction packets. - ֹͣ���ݰ�."){
}

NoPacket::~NoPacket(){
}

std::string NoPacket::getModuleName()
{
	return "NoPacket";
}
