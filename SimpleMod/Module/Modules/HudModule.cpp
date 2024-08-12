#include "HudModule.h"

HudModule::HudModule() : IModule(0, Category::CLIENT, "Displays things like the ArrayList.") {
    //registerBoolSetting("Keystrokes", &keystrokes, keystrokes);
    //registerBoolSetting("Watermark", &watermark, watermark);
}

HudModule::~HudModule()
{
}

std::string HudModule::getModuleName(){
    return ("HUD");
}

void HudModule::onPostRender()
{
}

void HudModule::drawKeystroke(char key, const Vec2& pos)
{
}

void HudModule::drawMouseKeystroke(Vec2 pos, std::string keyString)
{
}
