#pragma once
#include "Packet.h"
class LoopbackPacketSender{
public:
	virtual ~LoopbackPacketSender();

	virtual __int32 send(Packet* packet);
	virtual __int32 sendToServer(Packet* packet);
	virtual __int32 sendToClient(const void* networkIdentifier, const Packet* packet, int a4);
	virtual __int32 fun();
	virtual __int32 sendToClients(const void* networkIdentifier, const Packet* packet);
	virtual __int64 sendBroadcast(const Packet* packet);
	virtual __int64 sendBroadcast(const void* networkIdentifier, int a3, const Packet* packet);
};

