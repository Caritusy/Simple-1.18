#pragma once
#include <string>
#include <vector>
#include <map>
#include <unordered_map>
#include <functional>
#include <d3dx11tex.h>
#include <D3DX11.h>
#include <D3D11.h>

class GuiControls{
public:
	static void Mainwindow();
	static bool Lockbutton(std::string str, bool* v);
	static bool Checkbox(std::string str, bool* v,bool* _enum, std::string enumstr);
	static bool Tab(const char* icon, std::string str, bool v);
	static bool OptButton(const char* icon, std::string str, bool v);
};

