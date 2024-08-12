#pragma once
#include "../Utils/easylogging++.h"

class Hwid_user{
private:
	static int expire_time;
	static std::string calculateMD5(const std::string& input);
public:
	static int getexpire_time() {
		return expire_time;
	}
	static bool fileauth();
	static bool isTime(int untime);
	static std::string GetUser();
	static std::string GetHwid();
	static std::string GetCpuId();
	static std::string GetBiosSerialNumber();
	static std::string GetVolumeSerialNumber();

};

