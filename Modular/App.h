#pragma once
#include "Window.h"
#include "DirTimer.h"
#include "Macros.h"
#include "ImguiManager.h"
#include "Camera.h"
#include "PointLight.h"
#include "LuaEmbed.h"
#include <set>
#include "Mesh.h"

class App
{
public:
	App();
	// master frame / message loop
	int Go();
	~App();
	static void HandleExternalMessage(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);
private:
	void DoFrame();
	void SpawnSimulationWindow() noexcept;
public:
	LuaEmbed lua;
private:
	int x = 0, y = 0;
	ImguiManager imgui;
	Window wnd;
	Camera cam;
	PointLight light;
	DirTimer timer;
	Model nanosuit{wnd.Gfx(), "Nanosuit.gltf"};
	//Model scottCawthon{ wnd.Gfx(), "Scott.gltf" };
	float speed_factor = 1.0f;
};