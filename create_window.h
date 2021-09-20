#pragma once
#include <fmod.hpp>
#include <thread>

#include "file.h"
#include "fullscreen.h"
#include "func.h"
#include "music.h"
#include "time_show.h"
#include "video.h"

LRESULT CALLBACK WndProc(HWND hwnd, UINT message, WPARAM wparam, LPARAM lparam);

int ShowMeTheWindow()
{
	WNDCLASS windowClass = { 0 };
	windowClass.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH);
	windowClass.hCursor = LoadCursor(NULL, IDC_ARROW);
	windowClass.hInstance = NULL;
	windowClass.lpfnWndProc = WndProc;
	windowClass.lpszClassName = L"Window in Console";
	windowClass.style = CS_HREDRAW | CS_VREDRAW;

	HWND windowHandle;

	HWND windowHandle = CreateWindow(L"Window in Console", NULL, WS_POPUP, 0, 0, 300, 300, NULL, NULL, NULL, NULL);

	HWND hConsole = GetConsoleWindow();

	SetParent(windowHandle, hConsole); //a will be the new parent b
	DWORD style = GetWindowLong(windowHandle, GWL_STYLE); //get the b style
	style &= ~(WS_POPUP | WS_CAPTION); //reset the "caption" and "popup" bits
	style |= WS_CHILD; //set the "child" bit
	SetWindowLong(windowHandle, GWL_STYLE, style); //set the new style of b
	RECT rc; //temporary rectangle
	GetClientRect(hConsole, &rc); //the "inside border" rectangle for a
	MoveWindow(windowHandle, 0, 0, 400, 300, true); //place b at (x,y,w,h) in a
	UpdateWindow(hConsole);

	return 0;
}

LRESULT CALLBACK WndProc(HWND hwnd, UINT message, WPARAM wparam, LPARAM lparam)
{
	switch (message)
	{
	case WM_CHAR: //this is just for a program exit besides window's borders/task bar
		if (wparam == VK_ESCAPE)
		{
			DestroyWindow(hwnd);
		}
	case WM_DESTROY:
		PostQuitMessage(0);
		break;
	default:
		return DefWindowProc(hwnd, message, wparam, lparam);
	}
	return 0;
}