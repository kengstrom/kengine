#include "Window.h"



Window::Window()
{
	window_height = 100;
	window_width = 100;
}


Window::~Window()
{
}


LRESULT Window::handleEvent(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	switch (uMsg)
	{
	case WM_ACTIVATE:
	{
		/*
		if (!HIWORD(wParam))
			activate();
		else
			deactivate();
			*/
		return 0;
	}

	case WM_SYSCOMMAND:
	{
		switch (wParam)
		{
		case SC_SCREENSAVE:
		case SC_MONITORPOWER:
			return 0;
		}
		break;
	}

	case WM_SIZE:
	{
		//Graphics* graphics = dynamic_cast<Graphics*>(Singleton<SystemManager>::getInstance().getSystem(SystemType::GRAPHICS_SYSTEM));
		//graphics->onResize(LOWORD(lParam), HIWORD(lParam));
		return 0;
	}

	case WM_CLOSE:
	{
		PostQuitMessage(0);
		return 0;
	}
	}

	return DefWindowProc(hWnd, uMsg, wParam, lParam);
}

bool Window::createWindow()
{
	this->window_rect = createWindowRect();

	this->window_classname = getWindowClassName();
	this->window_title = getWindowTitle();

	if (!RegisterClass(&createWindowClass()))
	{
		int value = GetLastError();
		//Singleton<Logger>::getInstance().log(_T("Register \"WNDCLASS\" failed."), LOGTYPE_ERROR);
		return FALSE;
	}
	
	if (!setupWindow())
		return FALSE;
	/*
	if (!errorHandling())
		return FALSE;
		*/
	ShowWindow(this->handle_window, SW_SHOW);
	SetForegroundWindow(this->handle_window);
	SetFocus(this->handle_window);

	return TRUE;
}

long Window::getWindowWidth() const
{
	return window_width;
}
long Window::getWindowHeight() const
{
	return window_height;
}

RECT Window::createWindowRect()
{
	return RECT
	{
		(long)0,
		(long)0,
		(long)getWindowWidth(),
		(long)getWindowHeight()
	};
}

RECT Window::getWindowRect() const
{
	return this->window_rect;
}

const std::wstring Window::getWindowTitle() const
{
	return _T("TITLE");
}
const std::wstring Window::getWindowClassName() const
{
	return _T("CLASS");
}

WNDCLASS Window::createWindowClass()
{
	LPCTSTR window_classname = getWindowClassName().c_str();

	WNDCLASS wc;
	memset(&wc, NULL, sizeof(WNDCLASS));

	wc.style = CS_HREDRAW | CS_VREDRAW | CS_OWNDC;
	wc.lpfnWndProc = (WNDPROC)WndProc;
	wc.cbClsExtra = 0;
	wc.cbWndExtra = 0;
	wc.hInstance = this->handle_instance;

	//TODO: load the cursor and application icon!
	wc.hIcon = LoadIcon(NULL, IDI_WINLOGO);
	wc.hCursor = LoadCursor(NULL, IDC_ARROW);

	wc.hbrBackground = NULL;
	wc.lpszMenuName = NULL;

	wc.lpszClassName = this->window_classname.c_str();

	return wc;
}

LRESULT CALLBACK Window::WndProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	if (uMsg == WM_CREATE)
	{
		// if the message is WM_CREATE, the lParam contains a pointer to a CREATESTRUCT
		// the CREATESTRUCT contains the "this" pointer from the CreateWindow method
		// the "this" pointer of our app is stored in the createstruct pcs->lpCreateParams
		CREATESTRUCT *pCS = (CREATESTRUCT*)lParam;
		SetWindowLongPtr(hWnd, GWLP_USERDATA, (LONG_PTR)pCS->lpCreateParams);
	}
	else
	{
		//retrieve the stored "this" pointer
		Window* window = (Window*)(GetWindowLongPtr(hWnd, GWLP_USERDATA));
		if (window != nullptr)
			return window->handleEvent(hWnd, uMsg, wParam, lParam);
	}
	return DefWindowProc(hWnd, uMsg, wParam, lParam);
}

bool Window::setupWindow()
{
	this->handle_window = CreateWindowEx(this->extended_style,
		this->window_classname.c_str(),
		this->window_title.c_str(),
		this->style |
		WS_CLIPSIBLINGS |
		WS_CLIPCHILDREN,
		//getWindowPosition().x, getWindowPosition().y,
		100, 100,
		this->window_rect.right - this->window_rect.left,
		this->window_rect.bottom - this->window_rect.top,
		NULL,
		NULL,
		this->handle_instance,
		this);

	int error = GetLastError();
	if (!this->handle_window)
	{
		//Singleton<Logger>::getInstance().log(_T("Creation of our window failed."), LOGTYPE_ERROR);
		return FALSE;
	}

	return TRUE;
}