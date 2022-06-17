#pragma once
#include "Window.h"
#include "DirTimer.h"
#include "Macros.h"

class App
{
public:
	App();
	// master frame / message loop
	int Go();
	~App();
private:
	void DoFrame();
private:
	Window wnd;
	DirTimer timer;
	std::vector<std::unique_ptr<class Drawable>> drawables;
	static constexpr size_t nDrawables = 180;
};