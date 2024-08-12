#include "GuiMod.h"

ClickGuiMod::ClickGuiMod():IModule(VK_F6,Category::CLIENT, "The clickgui - toggle everything just by clicking on it!"){
}

ClickGuiMod::~ClickGuiMod()
{
}

std::string ClickGuiMod::getModuleName()
{
    return "Gui";
}

void ClickGuiMod::onDisable()
{
}

void ClickGuiMod::onEnable()
{
}
