#pragma once
// Visual C++ example
#include <dshow.h>
#include <cstdio>
#include <iostream>
#include <windows.h>

#include "fullscreen.h"

// For IID_IGraphBuilder, IID_IMediaControl, IID_IMediaEvent
#pragma comment(lib, "strmiids.lib") 

// Obviously change this to point to a valid mp3 file.
//const wchar_t* filePath = L"C:/Users/QAZ/Desktop/Cockerel/sounds/right.mp3";
using namespace std;

int playmusic(string track_name)
{
    //string filePath = "C:/Users/QAZ/Desktop/Cockerel/sounds/right.mp3";
    const wchar_t* filePath = L"C:/Users/Shata/Desktop/Cockerel/sounds/right.mp3";

    if (track_name == "right") { filePath = L"C:/Users/Shata/Desktop/Cockerel/sounds/right.mp3"; }
    if (track_name == "wrong") { filePath = L"C:/Users/Shata/Desktop/Cockerel/sounds/wrong.mp3"; }
    if (track_name == "win") { filePath = L"C:/Users/Shata/Desktop/Cockerel/sounds/win.mp3"; }
    if (track_name == "lose") { filePath = L"C:/Users/Shata/Desktop/Cockerel/sounds/lose.mp3"; }
    if (track_name == "boom") { filePath = L"C:/Users/Shata/Desktop/Cockerel/sounds/boom.mp3"; }

    IGraphBuilder* pGraph = NULL;
    IMediaControl* pControl = NULL;
    IMediaEvent* pEvent = NULL;

    // Initialize the COM library.
    HRESULT hr = ::CoInitialize(NULL);
    if (FAILED(hr))
    {
        ::printf("ERROR - Could not initialize COM library");
        return 0;
    }

    // Create the filter graph manager and query for interfaces.
    hr = ::CoCreateInstance(CLSID_FilterGraph, NULL, CLSCTX_INPROC_SERVER,
        IID_IGraphBuilder, (void**)&pGraph);
    if (FAILED(hr))
    {
        ::printf("ERROR - Could not create the Filter Graph Manager.");
        return 0;
    }

    hr = pGraph->QueryInterface(IID_IMediaControl, (void**)&pControl);
    hr = pGraph->QueryInterface(IID_IMediaEvent, (void**)&pEvent);

    // Build the graph.
    hr = pGraph->RenderFile(filePath, NULL);
    if (SUCCEEDED(hr))
    {
        // Run the graph.
        hr = pControl->Run();
        if (SUCCEEDED(hr))
        {
            // Wait for completion.
            long evCode;
            pEvent->WaitForCompletion(INFINITE, &evCode);

            // Note: Do not use INFINITE in a real application, because it
            // can block indefinitely.
        }
    }
    // Clean up in reverse order.
    pEvent->Release();
    pControl->Release();
    pGraph->Release();
    ::CoUninitialize();
    return 0;
}

//int playmusicX(string xname)
int playmusicX()
{
    //string filePath = "C:/Users/QAZ/Desktop/Cockerel/sounds/right.mp3";
    const wchar_t* filePath = L"Game\\sounds\\Purgatory.mp3";

    //if (xname == "Purgatory") { filePath = L"C:/Users/Shata/Desktop/Cockerel/sounds/Purgatory.mp3"; }

    while (true)
    {
        IGraphBuilder* pGraph = NULL;
        IMediaControl* pControl = NULL;
        IMediaEvent* pEvent = NULL;

        // Initialize the COM library.
        HRESULT hr = ::CoInitialize(NULL);
        if (FAILED(hr))
        {
            ::printf("ERROR - Could not initialize COM library");
            return 0;
        }

        // Create the filter graph manager and query for interfaces.
        hr = ::CoCreateInstance(CLSID_FilterGraph, NULL, CLSCTX_INPROC_SERVER,
            IID_IGraphBuilder, (void**)&pGraph);
        if (FAILED(hr))
        {
            ::printf("ERROR - Could not create the Filter Graph Manager.");
            return 0;
        }

        hr = pGraph->QueryInterface(IID_IMediaControl, (void**)&pControl);
        hr = pGraph->QueryInterface(IID_IMediaEvent, (void**)&pEvent);

        // Build the graph.
        hr = pGraph->RenderFile(filePath, NULL);
        if (SUCCEEDED(hr))
        {
            // Run the graph.
            hr = pControl->Run();
            if (SUCCEEDED(hr))
            {
                // Wait for completion.
                long evCode;
                pEvent->WaitForCompletion(INFINITE, &evCode);

                // Note: Do not use INFINITE in a real application, because it
                // can block indefinitely.
            }
        }
        // Clean up in reverse order.
        pEvent->Release();
        pControl->Release();
        pGraph->Release();
        ::CoUninitialize();
    }
    return 0;
}

//int PlayMusicZ(const std::string& pFile)
int PlayMusicZ()
{
    std::string pFile = "Game\\sounds\\Purgatory.mp3";

    IGraphBuilder* pGraph = NULL;
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

    // Build the graph (convert unicode filename)
    size_t _size = mbstowcs(NULL, pFile.c_str(), 2); // Add 2 for ZT
    wchar_t* _wfile = new wchar_t[_size + 2];
    _size = mbstowcs(_wfile, pFile.c_str(), pFile.length() + 1); // Add 1 for ZT
    hr = pGraph->RenderFile(_wfile, NULL);
    delete[] _wfile;

    if (SUCCEEDED(hr))
    {
        // Run the graph.
        hr = pControl->Run();
        if (SUCCEEDED(hr))
        {
            // Wait for completion.
            long evCode;
            pEvent->WaitForCompletion(INFINITE, &evCode);

            // Note: Do not use INFINITE in a real application, because it
            // can block indefinitely.
        }
    }
    // Clean up in reverse order.	
    pEvent->Release();
    pControl->Release();
    pGraph->Release();
    CoUninitialize();

    return 0;
}