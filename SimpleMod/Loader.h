#pragma once

#include "../Utils/easylogging++.h"
#include "../Utils/logger.h"

#include <windows.h>

#include <iostream>
#include <string>
#include <vector>

#include "../Utils/Target.h"
#include "../Memory/GameData.h"
#include "../Memory/Hooks.h"

#include "MinHook/MinHook.h"
#include "../Utils/HMath.h"
#include "Module/ModuleManager.h"
#include "Command/CommandMgr.h"
#include "Config/ConfigManager.h"

class Loader{
public:
	static bool isRunning;
};

