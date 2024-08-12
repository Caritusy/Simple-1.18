#include "Clickgui.h"
#include <D3D11.h>
#include "../../include/ImGui/imgui.h"
#include "../../include/ImGui/backends/imgui_impl_win32.h"

#include "../../include/ImGui/gl3w.h"
#include "../../include/ImGui/backends/imgui_impl_opengl3.h"
#include "../../include/ImGui/backends/imgui_impl_opengl3_loader.h"

#include "../../include/ImGui/backends/imgui_impl_dx11.h"

#include "../Module/Modules/GuiMod.h"

#include "../../Utils/easylogging++.h"
#include <Windows.h>
#include "../../Utils/Json.hpp"
#include "../../Utils/ColorUtil.h"

#include "control.h"
static constexpr float textPaddingX = 2.0f;
static constexpr float textPaddingY = 1.0f;
static constexpr float textSize = 0.9f;
static constexpr float textHeight = textSize * 9.0f;
static constexpr float categoryMargin = 0.5f;
static constexpr float paddingRight = 13.5f;
static constexpr float crossSize = textHeight / 2.f;
static constexpr float crossWidth = 0.5f;
static constexpr float backgroundAlpha = 0.5f;

extern LRESULT ImGui_ImplWin32_WndProcHandler(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);
static WNDPROC oWndProcHandler = nullptr;
LRESULT __stdcall WndProc(const HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam) {
	if (ImGui_ImplWin32_WndProcHandler(hWnd, uMsg, wParam, lParam)) return true;
	return CallWindowProc(oWndProcHandler, hWnd, uMsg, wParam, lParam);
}
void Clickgui::renderTooltip(std::string* text){
	Vec2 windowSize = Game.getClientInstance()->getGuiData()->windowSize;

	Vec2 currentTooltipPos = Vec2(5.f, windowSize.y - 15.f);
	float textWidth = DrawUtils::getTextWidth(text, 0.9).x;
	Vec2 textPos = Vec2(
		currentTooltipPos.x + textPaddingX,
		currentTooltipPos.y);
	Vec4 rectPos = Vec4(
		currentTooltipPos.x - 2.f,
		currentTooltipPos.y - 2.f,
		currentTooltipPos.x + (textPaddingX * 2) + textWidth + 2.f,
		currentTooltipPos.y + textHeight + 2.f);


	DrawUtils::drawText(textPos, text, (255,255,255), textSize);
}
void Clickgui::renderCategory(Category category) {
	const char* categoryName = Clickgui::catToName(category);
	static auto Guimod=moduleMgr->getModule<ClickGuiMod>();
	//ImGui::SetWindowSize(ImVec2(50,50));
	bool showWindow = true;
	ImGui::Begin(categoryName, &showWindow, ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoCollapse| ImGuiWindowFlags_NoScrollbar);

	std::vector<std::shared_ptr<IModule>> moduleList;
	getModuleListByCategory(category, &moduleList);
	{
		for (auto& it : moduleList) {
			std::string label = it->getModuleName();
		}
	}
	for (auto& mod : moduleList) {
		std::string textStr = mod->getModuleName();
		{// Settings
			std::vector<SettingEntry*>* settings = mod->getSettings();
			for (auto setting : *settings) {
				if (strcmp(setting->name, "enabled") == 0 || strcmp(setting->name, "keybind") == 0)
					continue;

				switch (setting->valueType) {
				case ValueType::BOOL_T: {
					control::RadioButton(setting->name, &setting->value->_bool);
				}
				case ValueType::ENUM_T: {
				}
				case ValueType::FLOAT_T: {
				}
				case ValueType::INT_T: {
				
				}
				default: {
				/*	char alc[100];
					sprintf_s(alc, 100, "Not implemented (%s)", setting->name);*/
				}
				}
			}
		}
	
	}
	ImGui::End();
}

void Clickgui::getModuleListByCategory(Category category, std::vector<std::shared_ptr<IModule>>* modList) {
	auto lock = moduleMgr->lockModuleList();
	std::vector<std::shared_ptr<IModule>>* moduleList = moduleMgr->getModuleList();
	for (auto& it : *moduleList) {
		if (it->getCategory() == category)
			modList->push_back(it);
	}
}
void Clickgui::init(){
	
}

void Clickgui::render(){
	return;
	renderCategory(Category::COMBAT);
	renderCategory(Category::VISUAL);
	renderCategory(Category::MOVEMENT);
	renderCategory(Category::PLAYER);
	renderCategory(Category::WORLD);
	renderCategory(Category::MISC);
	renderCategory(Category::CLIENT);
}

void opengl::init(HDC hdc){
		static bool init = false;
		try {
			if (!init) {
				auto hwid = WindowFromDC(hdc);
				oWndProcHandler = (WNDPROC)SetWindowLongPtr(hwid, GWL_WNDPROC, (LONG)WndProc);
				ImGui::CreateContext();
				ImGui_ImplWin32_Init(hwid);

				gl3wInit();
				ImGuiIO& io = ImGui::GetIO();

				io.Fonts->AddFontFromFileTTF("Downloaded\\fusion-pixel-10px-monospaced-zh_hant.ttf", 20, nullptr, io.Fonts->GetGlyphRangesChineseFull());
				io.Fonts->AddFontFromFileTTF("data\\fonts\\Mojangles.ttf", 20, nullptr, io.Fonts->GetGlyphRangesChineseFull());
				io.Fonts->AddFontFromFileTTF("data\\fonts\\MinecraftTen.ttf", 13, nullptr, io.Fonts->GetGlyphRangesChineseFull());


				ImGui_ImplOpenGL3_Init();
				LOG(INFO) << "Using OpenGL renderer.";
				init = true;
			}
			ImGui_ImplOpenGL3_NewFrame();
			ImGui_ImplWin32_NewFrame();
			ImGui::NewFrame();

			static auto hudModule = moduleMgr->getModule<HudModule>();

			auto clickGuiModule = moduleMgr->getModule<ClickGuiMod>();
			auto windowSize = Game.getClientInstance()->getGuiData()->windowSize;


			moduleMgr->onPreRender();

			if (clickGuiModule->isEnabled()) {
				Clickgui::render();
			}
			bool shouldRenderWatermark = true;
			ImU32 color = ColorUtil::getRainbowColor(3, 0.5f, 1, 1);

			shouldRenderWatermark = hudModule->watermark && hudModule->isEnabled();
			//	DrawUtils::drawText({255,255}, "年的伟大伟大", color, 1.f, 0, 30.f);

			if (clickGuiModule->isEnabled()) {
				shouldRenderWatermark = false;
			}
			{
			//	if (shouldRenderWatermark) {
					constexpr float nameTextSize = 1.5f;
					constexpr float versionTextSize = 0.7f;
					static const float textHeight = (nameTextSize + versionTextSize * 0.7f /* We don't quite want the version string in its own line, just a bit below the name */) * DrawUtils::getFont(0)->FontSize;
					constexpr float borderPadding = 18;
					constexpr float margin = 5;

					static std::string name = "SimpleMod";
#ifdef _DEBUG
					static std::string version = "dev";
#elif defined _BETA
					static std::string version = "beta";
#else
					static std::string version = "public";
#endif
					float nameLength = DrawUtils::getTextWidth(&name, nameTextSize).x;
					float fullTextLength = nameLength + DrawUtils::getTextWidth(&version).x;
					Vec4 rect = Vec4(
						windowSize.x - margin - fullTextLength - borderPadding * 2,
						windowSize.y - margin - textHeight,
						windowSize.x - margin - borderPadding,
						windowSize.y - margin);

					//DrawUtils::drawRectangle(rect, color, 1.f, 2.f);
				//	DrawUtils::fillRectangle(rect, (12, 12, 12), 1.f);

					DrawUtils::drawText(Vec2(0, 0), &name, color);
					//	DrawUtils::drawText(Vec2(nameLength+ fullTextLength * 2,0.f), &version,color);
		//		}

			}


			ImGui::EndFrame();
			ImGui::Render();
			ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
		}
		catch (...) {
			Game.getGuiData()->displayClientMessageF("%s%s%sOpenGL failure.", RED, BOLD, RESET);
			LOG(INFO) << "OpenGL failure.";
			return;
		}
		
}

void opengl::disable(){
	LOG(INFO) << "opengl disable.";
	ImGui_ImplOpenGL3_Shutdown();
	ImGui_ImplWin32_Shutdown();
	ImGui::DestroyContext();
	if (oWndProcHandler) {
		auto hwid = WindowFromDC(GetDC(NULL)); // Or use the stored HDC
		SetWindowLongPtr(hwid, GWL_WNDPROC, (LONG_PTR)oWndProcHandler);
		oWndProcHandler = NULL;
	}
}
static ID3D11RenderTargetView* mainRenderTargetView = nullptr;
void D3D11::init(IDXGISwapChain* pSwapChain, UINT SyncInterval, UINT Flags)
{
    static bool init = false;
    try {
		static ID3D11Device* pDevice = nullptr;
		static ID3D11DeviceContext* pContext = nullptr;
		static ID3D11Texture2D* pBackBuffer = nullptr;
        if (!init) {
			if (SUCCEEDED(pSwapChain->GetDevice(__uuidof(ID3D11Device), (void**)&pDevice))){
                pDevice->GetImmediateContext(&pContext);
                DXGI_SWAP_CHAIN_DESC sd;
                pSwapChain->GetDesc(&sd);
				auto hwid = sd.OutputWindow;
				pSwapChain->GetBuffer(0, __uuidof(ID3D11Texture2D), (LPVOID*)&pBackBuffer);
				pDevice->CreateRenderTargetView(pBackBuffer, NULL, &mainRenderTargetView);
				pBackBuffer->Release();
                oWndProcHandler = (WNDPROC)SetWindowLongPtr(hwid, GWLP_WNDPROC, (LONG_PTR)WndProc);
                ImGui::CreateContext();

                ImGuiIO& io = ImGui::GetIO();
				io.Fonts->AddFontFromFileTTF("Downloaded\\fusion-pixel-10px-monospaced-zh_hant.ttf", 20, nullptr, io.Fonts->GetGlyphRangesChineseFull());
				io.Fonts->AddFontFromFileTTF("data\\fonts\\Mojangles.ttf", 20, nullptr, io.Fonts->GetGlyphRangesChineseFull());
				io.Fonts->AddFontFromFileTTF("data\\fonts\\MinecraftTen.ttf", 13, nullptr, io.Fonts->GetGlyphRangesChineseFull());

                io.ConfigFlags |= ImGuiConfigFlags_NoMouseCursorChange;
                ImGui_ImplWin32_Init(hwid);
                ImGui_ImplDX11_Init(pDevice, pContext);
				LOG(INFO) << "Using D3D11 renderer.";
                init = true;
            }
            else  return;
        }
		if (!mainRenderTargetView) {
			ID3D11Texture2D* pBackBuffer = nullptr;
			pSwapChain->GetBuffer(0, __uuidof(ID3D11Texture2D), (LPVOID*)&pBackBuffer);
			pDevice->CreateRenderTargetView(pBackBuffer, NULL, &mainRenderTargetView);
			pBackBuffer->Release();
		}

        ImGui_ImplDX11_NewFrame();
        ImGui_ImplWin32_NewFrame();
        ImGui::NewFrame();

		static auto hudModule = moduleMgr->getModule<HudModule>();

		auto clickGuiModule = moduleMgr->getModule<ClickGuiMod>();
		auto windowSize = Game.getClientInstance()->getGuiData()->windowSize;

        moduleMgr->onPreRender();

        if (clickGuiModule && clickGuiModule->isEnabled()) {
            Clickgui::render();
        }
		bool shouldRenderWatermark = true;
		ImU32 color = ColorUtil::getRainbowColor(3, 0.5f, 1, 1);

		shouldRenderWatermark = hudModule->watermark && hudModule->isEnabled();
	//	DrawUtils::drawText({255,255}, "年的伟大伟大", color, 1.f, 0, 30.f);

		if (clickGuiModule->isEnabled()) {
			shouldRenderWatermark = false;
		}
		{
			if (shouldRenderWatermark) {
				constexpr float nameTextSize = 1.5f;
				constexpr float versionTextSize = 0.7f;
				static const float textHeight = (nameTextSize + versionTextSize * 0.7f /* We don't quite want the version string in its own line, just a bit below the name */) * DrawUtils::getFont(0)->FontSize;
				constexpr float borderPadding = 18;
				constexpr float margin = 5;

				static std::string name = "SimpleMod";
#ifdef _DEBUG
				static std::string version = "dev";
#elif defined _BETA
				static std::string version = "beta";
#else
				static std::string version = "public";
#endif
				float nameLength = DrawUtils::getTextWidth(&name, nameTextSize).x;
				float fullTextLength = nameLength + DrawUtils::getTextWidth(&version).x;
				Vec4 rect = Vec4(
					windowSize.x - margin - fullTextLength - borderPadding * 2,
					windowSize.y - margin- textHeight,
					windowSize.x - margin - borderPadding,
					windowSize.y - margin);

				//DrawUtils::drawRectangle(rect, color, 1.f, 2.f);
			//	DrawUtils::fillRectangle(rect, (12, 12, 12), 1.f);

				DrawUtils::drawText(Vec2(0,0), &name, color);
			//	DrawUtils::drawText(Vec2(nameLength+ fullTextLength * 2,0.f), &version,color);
			}
		
		}
		//DrawUtils::drawImage("Downloaded\\hacker.jpg", { 0,0 }, { 200,200 });

        ImGui::EndFrame();
        ImGui::Render();
        pContext->OMSetRenderTargets(1, &mainRenderTargetView, NULL);
        ImGui_ImplDX11_RenderDrawData(ImGui::GetDrawData());
    }
    catch (...) {
        Game.getGuiData()->displayClientMessageF("%s%s%sD3D11 failure.", RED, BOLD, RESET);
        LOG(INFO) << "D3D11 failure.";
        return;
    }
}

void D3D11::ResizeBuffers(IDXGISwapChain* pSwapChain, UINT BufferCount, UINT Width, UINT Height, DXGI_FORMAT NewFormat, UINT SwapChainFlags){
	if (mainRenderTargetView) { mainRenderTargetView->Release();mainRenderTargetView = nullptr; }
}

void D3D11::disable(){
	LOG(INFO) << "D3D11 disable.";
//	GameData::CleanUpDirectX();
	if (mainRenderTargetView) {
		mainRenderTargetView->Release();mainRenderTargetView = nullptr;
	//	ImGui_ImplDX11_Shutdown();
	//	ImGui_ImplWin32_Shutdown();
	//	ImGui::DestroyContext();
	}
}
