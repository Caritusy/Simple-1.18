#pragma once

#include "IModule.h"


class Tracer : public IModule {
private:
	int red = 255;
	int green = 255;
	int blue = 255;
public:
	Tracer();
	~Tracer();

	// Inherited via IModule
	virtual std::string getModuleName() override;
	//void onLevelRender() override;
	void onPreRender() override;
};