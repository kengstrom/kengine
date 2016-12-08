#include "Engine.h"



Engine::Engine()
{
	win.createWindow();
}


Engine::~Engine()
{
}

int Engine::mainloop()
{
	MSG msg = {};
	while (msg.message != WM_QUIT)
	{
		if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
		{
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}

		update();
		draw();
	}
	return msg.wParam;
}


int Engine::draw()
{
	return 0;
}

int Engine::update()
{
	return 0;
}