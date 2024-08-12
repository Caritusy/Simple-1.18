#pragma once
#include "../Module/ModuleManager.h"

class Guiprogram{
public:
	static void renderCategory(Category category);
	inline static void getModuleListByCategory(Category category, std::vector<std::shared_ptr<IModule>>* modList);
};

