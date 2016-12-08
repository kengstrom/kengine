#pragma once

#include <Windows.h>
#include <tchar.h>
#include <string>
class Window
{
public:
	Window();
	~Window();
	static LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);

	LRESULT handleEvent(HWND hwnd, UINT msg, WPARAM wparam, LPARAM lparam);

	long getWindowWidth() const;
	long getWindowHeight() const;

	const std::wstring getWindowTitle() const;
	const std::wstring getWindowClassName() const;
	bool createWindow();
protected:

	RECT getWindowRect() const;

private:
	WNDCLASS createWindowClass();
	RECT createWindowRect();
	bool setupWindow();

	RECT			window_rect;

	DWORD			extended_style;
	DWORD			style;

	unsigned int	pixel_format;

	std::wstring	window_classname;
	std::wstring	window_title;

	long			window_width;
	long			window_height;

	HDC             handle_devicecontext;
	HWND            handle_window;
	HINSTANCE       handle_instance;
};

