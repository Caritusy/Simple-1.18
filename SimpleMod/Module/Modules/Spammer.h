#pragma once
#include "IModule.h"
#include "../ModuleManager.h"
#include "../../../Utils/TimerUtil.h"
class Spammer:public IModule {
private:
	bool bypass = true;
	bool Import = false;
	float delay = 80.f;
	TimerUtil delayTime;
	int length = 10;
	std::string message = std::string(GOLD)+u8"��Simplemod����8848�ѽ��ֻ��͸���������һ�����õ�����ʮ�˴�!"/*+u8";����橖�������"*/;
	C_TextPacket textPacket;
	std::string path = "";
public:
	Spammer();
	~Spammer();

	inline std::string& getpath() { return path; };
	inline std::string& getMessage() { return message; };
	inline float& getDelay() { return delay; };
	inline int& getLength() { return length; };
	inline bool& getBypass() { return bypass; };

	// Inherited via IModule
	virtual void onDisable() override;
	virtual void onEnable() override;
	virtual std::string getModuleName() override;
	virtual void onTick(GameMode* gm) override;
};

