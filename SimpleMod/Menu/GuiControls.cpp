#include "GuiControls.h"
#include <SDL/include/SDL.h>
#include "Guiprogram.h"
#include "hashes.hpp"

#define IMGUI_DEFINE_MATH_OPERATORS
#include "../../include/imgui/imgui.h"
#include "../../include/imgui/imgui_internal.h"
using namespace ImGui;

struct color_t {

public:
    float r, g, b, a;

    inline ImColor to_im_color(float alpha = 1.f, bool use_gl_alpha = true) {

        return ImColor(r, g, b, (a * (use_gl_alpha ? GetStyle().Alpha : 1.f)) * alpha);
    }

    inline ImVec4 to_vec4(float alpha = 1.f, bool use_gl_alpha = true) {

        return ImVec4(r, g, b, (a * (use_gl_alpha ? GetStyle().Alpha : 1.f)) * alpha);
    }

};

color_t text = { 1.f, 1.f, 1.f, 1.f };
color_t frame_inactive = { 0.023f, 0.039f, 0.07f, 1.f };
color_t frame_active = { 0.043f, 0.07f, 0.137f, 1.f };
color_t text_disabled = { 0.51f, 0.52f, 0.56f, 1.f };
color_t border = { 1.f, 1.f, 1.f, 0.03f };
color_t accent_color = { 0.3f, 0.49f, 1.f, 1.f };

void GuiControls::Mainwindow(){
    ImGuiIO& io = ImGui::GetIO();
    SetNextWindowSize(ImVec2(905, 624));
    {ImGui::Begin(u8"☠Die_QwQ", NULL, ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoSavedSettings | ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoScrollbar | ImGuiWindowFlags_NoScrollWithMouse | ImGuiWindowFlags_NoBackground);
    ImVec2 P1, P2;
    ImDrawList* pDrawList;
    const auto& pos = ImGui::GetWindowPos();
    const auto& pWindowDrawList = ImGui::GetWindowDrawList();
    const auto& pBackgroundDrawList = ImGui::GetBackgroundDrawList();
    const auto& pForegroundDrawList = ImGui::GetForegroundDrawList();
    pBackgroundDrawList->AddRectFilled(ImVec2(0.000f + pos.x, 0.000f + pos.y), ImVec2(905 + pos.x, 624 + pos.y), ImColor(9, 9, 9, 180), 10); // Background
    pWindowDrawList->AddRectFilledMultiColor(ImVec2(20.000f + pos.x, 75.000f + pos.y) + ImVec2(0.000f, 0.000f), ImVec2(903 + pos.x, 76 + pos.y), ImColor(0.5, 0.200f, 0.200f, 0.800f), ImColor(0.00f, 0.00f, 0.00f, 0.000f), ImColor(0.00f, 0.00f, 0.00f, 0.000f), ImColor(0.5, 0.200f, 0.200f, 0.100f));
    pWindowDrawList->AddRectFilledMultiColor(ImVec2(20.000f + pos.x, 76.000f + pos.y) + ImVec2(0.000f, 0.000f), ImVec2(903 + pos.x, 77 + pos.y), ImColor(0.2, 0.200f, 0.200f, 0.800f), ImColor(0.00f, 0.00f, 0.00f, 0.000f), ImColor(0.00f, 0.00f, 0.00f, 0.000f), ImColor(0.2, 0.200f, 0.200f, 0.300f));
    pWindowDrawList->AddText(io.Fonts->Fonts[1], 40, pos + ImVec2(50 - io.Fonts->Fonts[1]->CalcTextSizeA(io.Fonts->Fonts[1]->FontSize, FLT_MAX, 0, ICON_FA_SHIELD_CROSS).x / 2 + 2, 20 + 2), GetColorU32(ImGuiCol_Text), ICON_FA_SHIELD_CROSS);
    pWindowDrawList->AddText(io.Fonts->Fonts[1], io.Fonts->Fonts[1]->FontSize, pos + ImVec2(180 - io.Fonts->Fonts[1]->CalcTextSizeA(io.Fonts->Fonts[1]->FontSize, FLT_MAX, 0, "SIMPLEMOD").x / 2 + 2, 20 + 2), accent_color.to_im_color(), "SIMPLEMOD");
    pWindowDrawList->AddText(io.Fonts->Fonts[1], io.Fonts->Fonts[1]->FontSize, pos + ImVec2(180 - io.Fonts->Fonts[1]->CalcTextSizeA(io.Fonts->Fonts[1]->FontSize, FLT_MAX, 0, "SIMPLEMOD").x / 2, 20), GetColorU32(ImGuiCol_Text), "SIMPLEMOD");
    pWindowDrawList->AddRectFilled(ImVec2(0.008f + pos.x, 0.080f + pos.y), ImVec2(190 + pos.x, 624 + pos.y), ImGui::GetColorU32(ImGuiCol_ChildBg), 10, ImDrawFlags_RoundCornersLeft);
  //  pWindowDrawList->AddText(io.Fonts->Fonts[2], io.Fonts->Fonts[2]->FontSize, pos + ImVec2(280 - io.Fonts->Fonts[2]->CalcTextSizeA(io.Fonts->Fonts[2]->FontSize, FLT_MAX, 0, "MISTERK!").x / 2, 20), GetColorU32(ImGuiCol_Text), "MISTERK!");
    ImGui::SetCursorPos(ImVec2(680, 21));
    if (OptButton(ICON_FA_THUMBS_UP, u8"赞助 MISTERK! 太吊了！", false))
        ShellExecuteA(NULL, "open", "https://afdian.net/a/QwQLL", NULL, NULL, SW_SHOWNORMAL);
    }
    static int tab_count = 0;
    ImGui::SetCursorPos(ImVec2(20, 120));
    BeginChild("##tabs", ImVec2(120, 624 - 50));
    if (Tab(ICON_FA_UTENSIL_KNIFE, "COMBAT", true) && tab_count != 0) { tab_count = 0; }
    if (Tab(ICON_FA_SHOE_PRINTS, "MOVEMENT", true) && tab_count != 1) { tab_count = 1; }
    if (Tab(ICON_FA_FROSTY_HEAD, "PLAYER", true) && tab_count != 2) { tab_count = 2; }
    if (Tab(ICON_FA_CAMPGROUND, "WORLD", true) && tab_count != 3) { tab_count = 3; }
    if (Tab(ICON_FA_COMMENT_DOTS, "MISC", true) && tab_count != 4) { tab_count = 4; }
    if (Tab(ICON_FA_EYE, "VISUAL", true) && tab_count != 5) { tab_count = 5; }
    if (Tab(ICON_FA_ARROW_UP, "CLIENT", true) && tab_count != 6) { tab_count = 6; }
    EndChild();
    ImGui::SetCursorPos(ImVec2(180, 120));
    ImGui::BeginChild("Editor", ImVec2(680, 480), true, ImGuiWindowFlags_NoScrollbar); {
       
            if (tab_count == 0) {
                Guiprogram::renderCategory(Category::COMBAT);
            }
            if (tab_count == 1) {
                Guiprogram::renderCategory(Category::MOVEMENT);
            }
            if (tab_count == 2) {
                Guiprogram::renderCategory(Category::PLAYER);
            }
            if (tab_count == 3) {
                Guiprogram::renderCategory(Category::WORLD);
            }
            if (tab_count == 4) {
                Guiprogram::renderCategory(Category::MISC);
            }
            if (tab_count == 5) {
                Guiprogram::renderCategory(Category::VISUAL);
            }
            if (tab_count == 6) {
                Guiprogram::renderCategory(Category::CLIENT);
            }
        }ImGui::EndChild();


        ImGui::End();
}

bool GuiControls::Lockbutton(std::string str, bool* v)
{
    return false;
}

bool GuiControls::Checkbox(std::string str, bool* v, bool* _enum,std::string enumstr){
    ImGuiWindow* window = GetCurrentWindow();
    ImDrawList* draw = window->DrawList;

    ImGuiContext& g = *GImGui;
    ImGuiStyle& style = g.Style;
    ImGuiID id = window->GetID(str.c_str());
    ImVec2 label_size = CalcTextSize(str.c_str(), NULL, true);

    str += *v ? " [ON] " : " [OFF] ";
    float w = GetWindowWidth();
    ImVec2 size = { 40, 18 };
    ImVec2 pos = window->DC.CursorPos;
  //  ImRect frame_bb(pos + ImVec2(GetWindowWidth() - (size.x+15), size.y), pos + ImVec2(GetWindowWidth() - (size.x+50), size.y+20));
    ImRect bb(pos, pos + ImVec2((GetWindowWidth()), 60));
    ItemAdd(bb, id);
    ItemSize(bb, GetStyle().FramePadding.y);
    bool enumhovered, enumheld;
    bool enumpressed = ButtonBehavior(bb, id, &enumhovered, &enumheld);
    if (ImGui::IsItemClicked() &&_enum!=nullptr) {

        *_enum = !(*_enum);
    }

    ImRect frame_bb(pos + ImVec2(w - (size.x+30),10), pos + ImVec2(w-30, (size.y+15)));
    ImRect total_bb(pos, pos + ImVec2(w, label_size.y));
    ItemAdd(total_bb, id);
    ItemSize(total_bb, style.FramePadding.y);

    bool hovered, held;
    bool pressed = ButtonBehavior(frame_bb, id, &hovered, &held);
    if (ImGui::IsItemClicked()) {
        *v = !(*v);

    }
    if (enumhovered && GetAsyncKeyState(VK_RBUTTON)) {
        BeginTooltipEx(ImGuiTooltipFlags_OverridePrevious, ImGuiWindowFlags_None | ImGuiWindowFlags_NoBackground);
        Text(enumstr.c_str());
        EndTooltip();
    }

    static std::unordered_map < ImGuiID, float > values;
    auto value = values.find(id);
    if (value == values.end()) {
        values.insert({ id, 0.f });
        value = values.find(id);
    }

    static std::unordered_map < ImGuiID, float > enumvalues;
    auto enumvalue = enumvalues.find(id);
    if (enumvalue == enumvalues.end()) {
        enumvalues.insert({ id, 0.f });
        enumvalue = enumvalues.find(id);
    }
   value->second = ImLerp(value->second, (*v ? 1.f : 0.f), g.IO.DeltaTime * 6.f);
   auto bbc = ImLerp(value->second,(hovered ? 1.f:0.f), g.IO.DeltaTime*2.f);
   enumvalue->second = ImLerp(value->second,(enumhovered ? 1.f:0.f), g.IO.DeltaTime*3.f);
   enumvalue->second *= style.Alpha;
   value->second *= style.Alpha;

   window->DrawList->AddRectFilledMultiColor(bb.Min + ImVec2(0.000f, 0.000f), bb.Max + ImVec2(bb.Min.x - bb.Min.x - 20, bb.Min.y - bb.Min.y), enumheld ? ImColor(enumvalue->second, 0.300f, 0.300f, 0.600f) : ImColor(9, 9, 9, 180), ImColor(0.00f, 0.00f, 0.00f, 0.000f), ImColor(0.00f, 0.00f, 0.00f, 0.000f), held ? ImColor(bbc, 0.400f, 0.100f, 0.800f) : ImColor(9, 9, 9, 80));
  
   window->DrawList->AddRectFilledMultiColor(bb.Min + ImVec2(0.000f, 0.000f), bb.Max + ImVec2(bb.Min.x - bb.Min.x - 20, bb.Min.y - bb.Min.y), enumhovered ? ImColor(enumvalue->second, 0.300f, 0.300f, 0.200f) : ImColor(9, 9, 9, 180), ImColor(0.00f, 0.00f, 0.00f, 0.000f), ImColor(0.00f, 0.00f, 0.00f, 0.000f), hovered ? ImColor(bbc, 0.400f, 0.100f, 0.400f) : ImColor(9, 9, 9, 80));
   window->DrawList->AddRectFilledMultiColor(bb.Min + ImVec2(0.000f, 0.000f), bb.Max + ImVec2(bb.Min.x - bb.Min.x - 20, bb.Min.y - bb.Min.y), *v ? ImColor(0, 255, 255, 60) : ImColor(255, 255, 255, 50), ImColor(0.00f, 0.00f, 0.00f, 0.000f), ImColor(0.00f, 0.00f, 0.00f, 0.000f), *v ? ImColor(bbc, 0.200f, 0.200f, 0.200f) : ImColor(9, 9, 9, 80));
   
    draw->AddText(ImGui::GetIO().Fonts->Fonts[2], ImGui::GetIO().Fonts->Fonts[2]->FontSize, ImVec2(bb.Min.x + 40, bb.GetCenter().y - label_size.y / 2), enumheld ? ImColor(enumvalue->second * 0.3f, 0.49f, 1.f, 0.5f) : ImColor(bbc * 255, 255.f, 255.f, 1.f), str.c_str());
    
     
    draw->AddRect(frame_bb.Min, frame_bb.Max, ImColor(value->second * 255.f, 255.f, 255.f, 0.2f),10);
    draw->AddCircleFilled(ImVec2(frame_bb.Min.x +7+ (25 * value->second), frame_bb.GetCenter().y), 7, *v|| hovered ? accent_color.to_im_color() : text_disabled.to_im_color(), 10);

    return pressed;
}

bool GuiControls::Tab(const char* icon,std::string str, bool v){
    ImGuiContext& g = *GImGui;
    const ImGuiStyle& style = g.Style;
    auto window = GetCurrentWindow();
    auto id = window->GetID(str.c_str());
    auto icon_size = CalcTextSize(icon);
    auto label_size = CalcTextSize(str.c_str(), 0, 1);
    auto pos = window->DC.CursorPos;
    auto draw = window->DrawList;
    ImRect bb(pos, pos + ImVec2(GetWindowWidth(), 55));
    ItemAdd(bb, id);
    ItemSize(bb, GetStyle().FramePadding.y);
    bool hovered, held;
    bool pressed = ButtonBehavior(bb, id, &hovered, &held);
    static std::unordered_map < ImGuiID, float > values;
    auto value = values.find(id);
    if (value == values.end()) {
        values.insert({ id, 0.f });
        value = values.find(id);
    }

    value->second = ImLerp(value->second, (held ? 1.f : 0.f), g.IO.DeltaTime * 6.f);
    value->second = ImLerp(value->second, (hovered ? 1.f : 0.f), g.IO.DeltaTime * 8.f);
    window->DrawList->AddRectFilledMultiColor(bb.Min + ImVec2(0.000f, 0.000f), bb.Max + ImVec2(bb.Min.x - bb.Min.x - 20, bb.Min.y - bb.Min.y), held ? ImColor(value->second, 0.200f, 0.200f, 0.600f) : ImColor(value->second, 0.200f, 0.200f, 0.400f), ImColor(0.00f, 0.00f, 0.00f, 0.000f), ImColor(0.00f, 0.00f, 0.00f, 0.000f), held ? ImColor(value->second, 0.200f, 0.200f, 0.300f) : ImColor(value->second, 0.200f, 0.200f, 0.100f));
    draw->AddText(ImGui::GetIO().Fonts->Fonts[0], ImGui::GetIO().Fonts->Fonts[0]->FontSize, ImVec2(bb.Min.x + 10, bb.GetCenter().y - label_size.y / 2)
        , held ? ImColor(value->second * 0.3f, 0.49f, 1.f, 0.5f) : ImColor(value->second * 255, 255.f, 255.f, 1.f), icon);
    draw->AddText(ImGui::GetIO().Fonts->Fonts[2], ImGui::GetIO().Fonts->Fonts[2]->FontSize + 2, ImVec2(bb.Min.x + 40, bb.GetCenter().y - label_size.y
        / 2), held ? ImColor(value->second * 0.3f, 0.49f, 1.f, 0.5f) : ImColor(value->second * 255, 255.f, 255.f, 1.f), str.c_str());

    return pressed;
}

bool GuiControls::OptButton(const char* icon, std::string str, bool v)
{
    ImGuiContext& g = *GImGui;
    const ImGuiStyle& style = g.Style;
    auto window = GetCurrentWindow();
    auto id = window->GetID(str.c_str());
    auto icon_size = CalcTextSize(icon);
    auto label_size = CalcTextSize(str.c_str(), 0, 1);
    auto pos = window->DC.CursorPos;
    auto draw = window->DrawList;
    ImRect bb(pos, pos + ImVec2(GetWindowWidth(), 30));
    ItemAdd(bb, id);
    ItemSize(bb, GetStyle().FramePadding.y);
    bool hovered, held;
    bool pressed = ButtonBehavior(bb, id, &hovered, &held);
    static std::unordered_map < ImGuiID, float > values;
    auto value = values.find(id);
    if (value == values.end()) {
        values.insert({ id, 0.f });
        value = values.find(id);
    }
    value->second = ImLerp(value->second, (held ? 1.f : 0.f), g.IO.DeltaTime * 3.f);
    value->second = ImLerp(value->second, (hovered ? 1.f : 0.f), value->second < 255.f ? g.IO.DeltaTime * 3.f : g.IO.DeltaTime -(g.IO.DeltaTime * 1.2f));

    draw->AddText(ImGui::GetIO().Fonts->Fonts[0], ImGui::GetIO().Fonts->Fonts[0]->FontSize,ImVec2(bb.Min.x + 10, bb.GetCenter().y - label_size.y / 2), held ? ImColor(value->second * 0.3f, 0.49f, 1.f, 0.5f) : ImColor(value->second * 255, 255.f, 255.f, 1.f), icon);
    draw->AddText(ImGui::GetIO().Fonts->Fonts[2], ImGui::GetIO().Fonts->Fonts[2]->FontSize + 2, ImVec2(bb.Min.x + 40, bb.GetCenter().y - label_size.y / 2), held ? ImColor(value->second * 0.3f, 0.49f, 1.f, 0.5f) : ImColor(value->second * 255, 255.f, 255.f, 1.f), str.c_str());



    return pressed;
}
