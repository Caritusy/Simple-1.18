#pragma once
#include <Windows.h>

#include <filesystem>
#include <fstream>
#include <string>
#pragma comment(lib, "runtimeobject")

#include "../../Utils/Json.hpp"
#include "../Command/CommandMgr.h"
#include "../Module/ModuleManager.h"
#include "../../Utils/easylogging++.h"
using json = nlohmann::json;

class ConfigManager {
private:
	std::wstring roamingFolder;
	static std::wstring GetRoamingFolderPath();
	json currentConfigObj;

public:
	ConfigManager();
	~ConfigManager();

	std::string currentConfig = "property";

	void loadConfig(std::string name, bool create);
	void saveConfig();
	void init();
};

extern ConfigManager* configMgr;
