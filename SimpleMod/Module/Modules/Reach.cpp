#include "Reach.h"
#include <Windows.h>
#include "../../../Utils/Utils.h"
#include "../../../Utils/logger.h"
Reach::Reach() :IModule('0',Category::COMBAT,"Increases your reach."){
	registerFloatSetting("Reach Value", &reachValue, reachValue, 3.f, 8.f);
}
Reach::~Reach()
{
}
std::string Reach::getModuleName()
{
	return  "Reach";
}
void Reach::onEnable(){
	static uintptr_t sigOffset = 0x0;
	if (sigOffset == 0x0) {
		sigOffset = GetOffsetFromSig("F3 0F 10 05 ? ? ? ? F3 0F 10 8D ? ? ? ? 0F 2F C8 76 0F C6 85",4);
		if (sigOffset != 0x0) {
			reachPtr = reinterpret_cast<float*>(sigOffset);
			originalReach = *reachPtr;
		}
	}
	if (!VirtualProtect(reachPtr, sizeof(float), PAGE_EXECUTE_READWRITE, &oldProtect)) {
#ifdef _DEBUG
		LOG(INFO)<<"couldnt unprotect memory send help";
		__debugbreak();
#endif
	}
}
void Reach::onDisable(){
	*reachPtr = originalReach;
	if (reachPtr != 0)
		VirtualProtect(reachPtr, sizeof(float), oldProtect, &oldProtect);
}
void Reach::onTick(GameMode* gm){
	if (reachPtr != 0) {
		*reachPtr = reachValue;
	}
}
