#pragma once

#include "Window.h"
class Engine
{
public:
	Engine();
	~Engine();

	int mainloop();
protected:
	int draw();
	int update();
	Window win;
};

