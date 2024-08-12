#include "ClientInstance.h"

void GuiData::displayClientMessageVA(const char* fmt, va_list lis, bool sendToInjector){
	auto lengthNeeded = _vscprintf(fmt, lis) + 1;
	if (lengthNeeded >= 300) {
		LOG(ERROR)<<"A message that was"<< lengthNeeded  <<"characters long could not be fitted into the buffer";
		return;
	}

	char message[300];
	vsprintf_s(message, 300, fmt, lis);
	std::string msg(message);
	displayClientMessage(&msg);
}

void GuiData::displayClientMessageF(const char* fmt, ...){
	va_list arg;
	va_start(arg, fmt);
	displayClientMessageVA(fmt, arg, true);
	va_end(arg);
}

void GuiData::displayClientMessageNoSendF(const char* fmt, ...){
	va_list arg;
	va_start(arg, fmt);
	displayClientMessageVA(fmt, arg, false);
	va_end(arg);
}

void GuiData::displayClientMessage(std::string* a2){
	using displayClientMessage = void(__thiscall*)(void*, TextHolder&);
	static displayClientMessage displayMessageFunc = reinterpret_cast<displayClientMessage>(FindSignature("55 8B EC 6A FF 68 ? ? ? ? 64 A1 00 00 00 00 50 81 EC DC 00 00 00 A1 ? ? ? ? 33 C5 89 45 F0 56 57 50 8D 45 ? 64 A3 00 00 00 00 89 8D ? ? ? ? 8B 45 ? 8D 8D ? ? ? ? 6A 00 C7 85 30 FF FF FF"));
	TextHolder text = TextHolder(*a2);
	if (displayMessageFunc != nullptr)
		displayMessageFunc(this, text);
}
