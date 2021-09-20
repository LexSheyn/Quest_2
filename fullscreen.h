#pragma once

#define _CRT_SECURE_NO_WARNINGS

#include <string>
#include <dshow.h>
#include <iostream>

#include "wtypes.h"

#pragma comment(lib, "strmiids.lib")
#pragma comment(lib, "quartz.lib")

#pragma warning(disable : 4996)

using namespace std;

// Get the horizontal and vertical screen sizes in pixel
int GetDesktopResolution(int& horizontal, int& vertical)
{
    RECT desktop;
    // Get a handle to the desktop window
    const HWND hDesktop = GetDesktopWindow();
    // Get the size of screen to the variable desktop
    GetWindowRect(hDesktop, &desktop);
    // The top left corner will have coordinates (0,0)
    // and the bottom right corner will have coordinates
    // (horizontal, vertical)
    horizontal = desktop.right;
    vertical = desktop.bottom;

    return 0;
}

int PlayVideo()
{
    std::string pFile = "Resources\\videos\\dead.mp4";

    IGraphBuilder* pGraph = NULL;
    IVideoWindow* pWin = NULL;
    IMediaControl* pControl = NULL;
    IMediaEvent* pEvent = NULL;

    // Initialize the COM library.
    HRESULT hr = CoInitialize(NULL);
    if (FAILED(hr)) return 1;

    // Create the filter graph manager and query for interfaces.
    hr = CoCreateInstance(CLSID_FilterGraph, NULL, CLSCTX_INPROC_SERVER, IID_IGraphBuilder, (void**)&pGraph);
    if (FAILED(hr)) return 1;

    // Get interfaces
    hr = pGraph->QueryInterface(IID_IMediaControl, (void**)&pControl);
    hr = pGraph->QueryInterface(IID_IMediaEvent, (void**)&pEvent);
    hr = pGraph->QueryInterface(IID_IVideoWindow, (void**)&pWin);

    // Build the graph (convert unicode filename)
    size_t _size = mbstowcs(NULL, pFile.c_str(), 2); // Add 2 for ZT
    wchar_t* _wfile = new wchar_t[_size + 2];
    _size = mbstowcs(_wfile, pFile.c_str(), pFile.length() + 1); // Add 1 for ZT
    hr = pGraph->RenderFile(_wfile, NULL);
    delete[] _wfile;

    RECT consoleWindow;
    const HWND hConsole = GetConsoleWindow();
    GetWindowRect(hConsole, &consoleWindow);

    pWin->put_Owner((OAHWND)hConsole);
    pWin->put_AutoShow(OAFALSE);
    pWin->put_WindowStyle(WS_CHILD | WS_CLIPSIBLINGS | WS_CLIPCHILDREN);
    pWin->put_BorderColor(RGB(0, 128, 0));
    pWin->put_MessageDrain((OAHWND)hConsole);
    pWin->SetWindowPosition(40, 0, 854, 480);
    pWin->SetWindowForeground(0);
    pWin->put_Visible(OATRUE);
    //pWin->HideCursor(OATRUE);

    /*
    CComQIPtr<IVideoWindow> pVideoWindow(m_pGraph);

    HRESULT hr = pVideoWindow->put_Owner((OAHWND)m_hWnd);
    hr = pVideoWindow->put_AutoShow(OAFALSE);
    hr = pVideoWindow->put_WindowStyle(WS_CHILD | WS_CLIPSIBLINGS | WS_CLIPCHILDREN);
    hr = pVideoWindow->put_BorderColor(RGB(0, 128, 0));
    hr = pVideoWindow->put_MessageDrain((OAHWND)m_hWnd);

    hr = pVideoWindow->SetWindowPosition(rctWindow.left, rctWindow.top, rctWindow.right - rctWindow.left + 1, rctWindow.bottom - rctWindow.top + 1);

    hr = pVideoWindow->SetWindowForeground(0);
    hr = pVideoWindow->put_Visible(OATRUE);
    */

    if (SUCCEEDED(hr))
    {
        hr = pControl->Run();
        if (SUCCEEDED(hr))
        {
            long evCode;
            pEvent->WaitForCompletion(INFINITE, &evCode);
        }
    }

    pControl->Stop();
    pWin->put_Visible(OAFALSE);
    pWin->put_Owner(NULL);

    pControl->Release();
    pEvent->Release();
    pWin->Release();
    pGraph->Release();
    CoUninitialize();

    return 0;
}

/*
int main()
{
    PlayVideo("D:\\dfs.avi"); // play any format Windows can handle, avi/mpg etc.
    return 0;
}
*/