#include "control.h"
#include <unordered_map>
#define IMGUI_DEFINE_MATH_OPERATORS
#include "ImGui/imgui.h"
#include "ImGui/imgui_internal.h"
using namespace ImGui;

bool control::RadioButton(const char* label, bool* active){
    auto window = GetCurrentWindow();
    auto id = window->GetID(label);
    auto label_size = CalcTextSize(label, 0, 1);

    auto pos = window->DC.CursorPos;
    auto draw = window->DrawList;

    ImGuiContext& g = *GImGui;
    const ImGuiStyle& style = g.Style;

    ImRect bb(pos, pos + ImVec2((GetWindowWidth()), 60));
    ItemAdd(bb, id);
    ItemSize(bb, GetStyle().FramePadding.y);

    bool hovered, held;
    bool pressed = ButtonBehavior(bb, id, &hovered, &held);
    if (pressed) {
        *active = !(*active);
        MarkItemEdited(id);
    }
    static std::unordered_map < ImGuiID, float > values;
    auto value = values.find(id);
    if (value == values.end()) {
        values.insert({ id, 0.f });
        value = values.find(id);
    }
    value->second = ImLerp(value->second, hovered ? 1.f : 0.150f, g.IO.DeltaTime * 5.f);
    value->second *= style.Alpha;
    value->second = ImLerp(value->second, held ? 1.f : 0.20f, g.IO.DeltaTime * 0.8f);

    window->DrawList->AddRectFilledMultiColor(bb.Min + ImVec2(0.000f, 0.000f), bb.Max + ImVec2(bb.Min.x - bb.Min.x - 20, bb.Min.y - bb.Min.y), held ? ImColor(value->second, 0.300f, 0.300f, 0.600f) : ImColor(9, 9, 9, 180), ImColor(0.00f, 0.00f, 0.00f, 0.000f), ImColor(0.00f, 0.00f, 0.00f, 0.000f), held ? ImColor(value->second, 0.400f, 0.100f, 0.800f) : ImColor(9, 9, 9, 80));
    window->DrawList->AddRectFilledMultiColor(bb.Min + ImVec2(0.000f, 0.000f), bb.Max + ImVec2(bb.Min.x - bb.Min.x - 20, bb.Min.y - bb.Min.y), hovered ? ImColor(value->second, 0.300f, 0.300f, 0.200f) : ImColor(9, 9, 9, 180), ImColor(0.00f, 0.00f, 0.00f, 0.000f), ImColor(0.00f, 0.00f, 0.00f, 0.000f), hovered ? ImColor(value->second, 0.400f, 0.100f, 0.400f) : ImColor(9, 9, 9, 80));
    window->DrawList->AddRectFilledMultiColor(bb.Min + ImVec2(0.000f, 0.000f), bb.Max + ImVec2(bb.Min.x - bb.Min.x - 20, bb.Min.y - bb.Min.y), *active ? ImColor(0, 255, 255, 60) : ImColor(255, 255, 255, 50), ImColor(0.00f, 0.00f, 0.00f, 0.000f), ImColor(0.00f, 0.00f, 0.00f, 0.000f), *active ? ImColor(value->second, 0.200f, 0.200f, 0.200f) : ImColor(9, 9, 9, 80));
    draw->AddText(ImGui::GetIO().Fonts->Fonts[2], ImGui::GetIO().Fonts->Fonts[2]->FontSize, ImVec2(bb.Min.x + 40, bb.GetCenter().y - label_size.y / 2), held ? ImColor(value->second * 0.3f, 0.49f, 1.f, 0.5f) : ImColor(value->second * 255, 255.f, 255.f, 1.f), label);
    return false;
}