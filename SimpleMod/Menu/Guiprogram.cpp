#include "Guiprogram.h"
#include "GuiControls.h"
#include "../../include/ImGui/imgui.h"
void Guiprogram::renderCategory(Category category){
    std::vector<std::shared_ptr<IModule>> moduleList;
    getModuleListByCategory(category, &moduleList);
    for (auto& mod : moduleList) {
        std::string textStr = mod->getModuleName();
        std::vector<SettingEntry*>* settings = mod->getSettings();
     
        for (auto setting : *settings) {
            if (strcmp(setting->name, "enabled") == 0 || strcmp(setting->name, "keybind") == 0)
                continue;
            if (setting->valueType == ValueType::BOOL_T) {
                GuiControls::Checkbox(setting->name, &setting->value->_bool,&setting->minValue->_bool,mod->getTooltip());
            }
            if ((setting->valueType == ValueType::ENUM_T || setting->valueType == ValueType::FLOAT_T || setting->valueType == ValueType::INT_T)&&setting->minValue->_bool) {
                if (setting->valueType == ValueType::FLOAT_T) {
                    ImGui::SliderFloat(setting->name, &setting->value->_float, setting->minValue->_float, setting->maxValue->_float);
                }
                if (setting->valueType == ValueType::INT_T) {
                    ImGui::SliderInt(setting->name, &setting->value->_int, setting->minValue->_int, setting->maxValue->_int);
                }
                if (setting->valueType == ValueType::ENUM_T) {
                  
                }
            }
        }
    }
}

inline void Guiprogram::getModuleListByCategory(Category category, std::vector<std::shared_ptr<IModule>>* modList){
    auto lock = moduleMgr->lockModuleList();
    std::vector<std::shared_ptr<IModule>>* moduleList = moduleMgr->getModuleList();
    for (auto& it : *moduleList) {
        if (it->getCategory() == category)
            modList->push_back(it);
    }
}
