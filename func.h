#pragma once
#include <iostream>
#include <fstream>
#include <cstring>
#include <string>
#include <windows.h>
#include <cstdio>
#include <cstdlib>
#include <conio.h>
#include <vector>
#include <iterator>
#include <algorithm>
#include <chrono>
#include <thread>

#include "fullscreen.h"

using namespace std;

void ClearScreen()
{
    HANDLE                     hStdOut;
    CONSOLE_SCREEN_BUFFER_INFO csbi;
    DWORD                      count;
    DWORD                      cellCount;
    COORD                      homeCoords = { 0, 0 };

    hStdOut = GetStdHandle(STD_OUTPUT_HANDLE);
    if (hStdOut == INVALID_HANDLE_VALUE) return;

    // Get the number of cells in the current buffer
    if (!GetConsoleScreenBufferInfo(hStdOut, &csbi)) return;
    cellCount = csbi.dwSize.X * csbi.dwSize.Y;

    // Fill the entire buffer with spaces
    if (!FillConsoleOutputCharacter(
        hStdOut,
        (TCHAR)' ',
        cellCount,
        homeCoords,
        &count
    )) return;

    // Fill the entire buffer with the current colors and attributes
    if (!FillConsoleOutputAttribute(
        hStdOut,
        csbi.wAttributes,
        cellCount,
        homeCoords,
        &count
    )) return;

    // Move the cursor home
    SetConsoleCursorPosition(hStdOut, homeCoords);
}
//======================================(Experimental)===================================
int CopyFileBinary()
{
    char* buffer;
    buffer = new char;

    ifstream infile("c:\\123.qwe", ios::binary);
    ofstream outfile("c:\\1234.qwe", ios::binary);

    while (!infile.eof())
    {
        infile.read(buffer, sizeof(char));
        outfile.write(buffer, sizeof(char));
    }
    delete buffer;

    return 0;
}

int CopyFileBin()
{
    std::ifstream input("C:\\Final.gif", std::ios::binary);
    std::ofstream output("C:\\myfile.gif", std::ios::binary);

    std::copy(
        std::istreambuf_iterator<char>(input),
        std::istreambuf_iterator<char>(),
        std::ostreambuf_iterator<char>(output));

    return 0;
}

int CopyFToFBin()
{
    std::ifstream f1("C:\\me.txt", std::fstream::binary);

    std::ofstream f2("C:\\me2.doc", std::fstream::trunc | std::fstream::binary);

    f2 << f1.rdbuf();

    return 0;
}

int CopyFileBinBuf()
{
    std::ifstream input("C:\\Final.gif", std::ios::binary);

    // copies all data into buffer
    std::vector<unsigned char> buffer(std::istreambuf_iterator<char>(input), {});

    return 0;
}

string readFile2(const string& fileName)
{
    ifstream ifs(fileName.c_str(), ios::in | ios::binary | ios::ate);

    ifstream::pos_type fileSize = ifs.tellg();
    ifs.seekg(0, ios::beg);

    vector<char> bytes(fileSize);
    ifs.read(bytes.data(), fileSize);

    return string(bytes.data(), fileSize);
}
//=======================================================================================
    //system("start chrome.exe");

    //::ShowWindow(::GetConsoleWindow(), SW_HIDE);  // SW_HIDE  SW_RESTORE  SW_SHOW
    //Sleep(2000);
    //::ShowWindow(::GetConsoleWindow(), SW_RESTORE);

void Stealth()
{
    HWND Stealth;
    AllocConsole();
    Stealth = FindWindowA("ConsoleWindowClass", NULL);
    ShowWindow(Stealth, 0);
}

bool IsConsoleVisible()
{
    return ::IsWindowVisible(::GetConsoleWindow()) != FALSE;
}

char skip_symbol;
int SKIP_S;

//void SkipWriting(char& symbol)
void SkipWriting(int s)
{
    //char c;
    //c = _getch();
    //symbol = c;
    //skip_symbol = _getch();
    //symbol = skip_symbol;
    s = kbhit();

    //return kbhit();
}

void Fu1()
{
    Sleep(5000);
    keybd_event(0x41, 0, 0, 0);
    keybd_event(0x41, 0, KEYEVENTF_KEYUP, 0);
}

DWORD WINAPI Thread_1(LPVOID lpParameter)
{
    std::cout << "I'am The THREAD: " << GetCurrentThreadId();

    return 0;
}

void write(std::string text)
{
    std::string input = text;

    for (int i = 0; i < input.length(); i++)
    {   
        for (int j = 0; j < 10; j++) // Delay ~ 1 ms
        {
            std::cout << " ";
            std::cout << "\b";
        }
        std::cout << input[i];
    }
}

int WriteTEST(std::string text, char &symbol)
{
    std::string input = text;

    int result = 0;

    for (int i = 0; i < input.length(); i++)
    {
        if (kbhit())
        {
            if ((GetAsyncKeyState(VK_RETURN) & 0x8000) or (GetAsyncKeyState(VK_SPACE) & 0x8000) or (GetAsyncKeyState(0x49) & 0x8000))
            {
                result = 1;
                ClearScreen();
                std::cout << input;
                break;
            }
        }
        std::cout << input[i];
        Sleep(10);
    }

    if (result == 1)
    {
        if (!(GetAsyncKeyState(VK_SPACE) & 0x8000) and !(GetAsyncKeyState(0x49) & 0x8000))
        {
            do
            {
                symbol = _getch();
            } while (symbol != 13);
        }
    }

    return result;
}

void WriteSpeed(string text, int ns)
{
    string a = text;
    int time = ns;

    for (int i = 0; i < a.length(); i++)
    {
        //Sleep(time);
        std::this_thread::sleep_for(std::chrono::nanoseconds(time));

        cout << a[i];
    }
}

void outdel(string text, int speed)
{
    string t = text;
    int time = speed;       // Milliseconds
    //int del = delay;        // Milliseconds
    int len = t.length();

    for (int i = 0; i < t.length(); i++)
    {
        //Sleep(time);

        cout << t[i];
    }

    //Sleep(del);

    cout << string(t.length(), '\b');

    for (int i = 0; i < t.length(); i++)
    {
        for (int i = 0; i < len; i++)
        {
            //Sleep(time);

            cout << t[i];
        }
        Sleep(15);
        cout << string(len, '\b');
        cout << string(len, ' ');
        cout << string(len, '\b');
        len--;
    }
}

int Next(char& symbol, int& menu_mark)
{
    std::string continune = ">> Next...";

    char c = '0';

    std::cout << "\n\n    ";
    std::cout << continune;
        
    c = _getch();   // 'ESC' = 27

    if (c == ' ')
    {
        menu_mark = 1;
    }
    else if (c == 'i' or c == 'I' or c == 'ø' or c == 'Ø')
    {
        menu_mark = 3;
    }
    else
    {
        c = '0';
    }
    
    symbol = c;
    
    return 0;
}

int NextIntro(char& symbol, int& menu_mark, int& intro_number)
{
    std::string continune = ">> Next...";

    char c = '0';

    std::cout << "\n\n    ";
    std::cout << continune;

    while (c != 13 and c != ' ' and c != 'i' and c != 'I' and c != 'ø' and c != 'Ø')
    {
        c = _getch();   // 'ESC' = 27

        if (c == ' ')
        {
            menu_mark = 1;
        }
        else if (c == 'i' or c == 'I' or c == 'ø' or c == 'Ø')
        {
            menu_mark = 3;
        }
        else if (c == 13)
        {
            intro_number++;
        }
    }

    symbol = c;

    return 0;
}

int NextIntroTEST(char &symbol, int& menu_mark, int& intro_number)
{
    std::string continune = ">> Next...";

    char c = '0';

    std::cout << "\n\n    ";
    std::cout << continune;

    while (c != 13 and c != ' ' and c != 'i' and c != 'I' and c != 'ø' and c != 'Ø')
    {
        c = _getch();   // 'ESC' = 27

        if (c == ' ')
        {
            menu_mark = 1;
        }
        else if (c == 'i' or c == 'I' or c == 'ø' or c == 'Ø')
        {
            menu_mark = 3;
        }
        else if (c == 13)
        {
            intro_number++;
        }
    }

    symbol = c;

    return 0;
}

int NextTEST(char& symbol, int& menu_mark)
{
    std::string continune = ">> Next...";

    char c = '0';

    std::cout << "\n\n    ";
    std::cout << continune;

    while (c != 13 and c != ' ' and c != 'i' and c != 'I' and c != 'ø' and c != 'Ø')
    {
        c = _getch();   // 'ESC' = 27

        if (c == ' ')
        {
            menu_mark = 1;
        }
        else if (c == 'i' or c == 'I' or c == 'ø' or c == 'Ø')
        {
            menu_mark = 3;
        }
    }

    symbol = c;

    return 0;
}

void NextX()
{
    string continune = ">> Next...";
    cout << "\n\n    ";
    cout << continune;
}

void end()
{
    string continune = ">> THE END";
    cout << "\n\n    ";
    cout << continune;
}

void restart()
{
    string continune = ">> RESTART";
    cout << "\n\n    ";
    cout << continune;
}

int Restart(char& symbol, int& chapter, int game_start)
{
    ClearScreen();

    std::string continune = ">> RESTART";

    char c = '0';

    std::cout << "\n\n    ";
    std::cout << continune;

    c = _getch();   // 'ESC' = 27
    if (c == 27) { exit(0); }

    c = '0';

    symbol = c;
    chapter = game_start;

    return 0;
}

//void flashtext(string text, int delay, int time)
void FlashTextOLD(string text)
{
    //cout << "> ";
    //std::cout << "\n\n    ";

    for (int i = 0; i < 4; i++)
    {
        cout << text;
        //Sleep(100);
        std::this_thread::sleep_for(std::chrono::nanoseconds(100000000)); // 100.000.000
        cout << string(text.length(), '\b');
        cout << string(text.length(), ' ');
        //Sleep(100);
        std::this_thread::sleep_for(std::chrono::nanoseconds(100000000)); // 100.000.000
        cout << string(text.length(), '\b');
        //clearscreen();
        //Sleep(200);
    }
    ClearScreen();
}

HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);

void FlashText(string text)
{
    for (int i = 0; i < 4; i++)
    {
        SetConsoleTextAttribute(hConsole, 8); // 8 - Dark

        std::cout << text;

        std::this_thread::sleep_for(std::chrono::nanoseconds(100000000)); // 100.000.000

        std::cout << string(text.length(), '\b');

        SetConsoleTextAttribute(hConsole, 15); // 15 - White

        std::cout << text;

        std::this_thread::sleep_for(std::chrono::nanoseconds(100000000)); // 100.000.000

        std::cout << string(text.length(), '\b');

        SetConsoleTextAttribute(hConsole, 7); // 7 - Default

    }
    ClearScreen();
}

void FlashTextLong(string text)
{
    for (int i = 0; i < 4; i++)
    {
        cout << text;
        //Sleep(300);
        std::this_thread::sleep_for(std::chrono::nanoseconds(300000000)); // 300.000.000
        cout << string(text.length(), '\b');
        cout << string(text.length(), ' ');
        //Sleep(300);
        std::this_thread::sleep_for(std::chrono::nanoseconds(300000000)); // 300.000.000
        cout << string(text.length(), '\b');
        //clearscreen();
        //Sleep(200);
    }
}

void dead()
{
    ClearScreen();
    string continune = "YOU DIED";
    cout << "\n\n    ";
    FlashTextLong(continune);
    cout << continune;
    //Sleep(1000);
    std::this_thread::sleep_for(std::chrono::seconds(1)); // 1s
    cout << "\n\n    ";
    cout << "Press any key to continune...";
}

//int Dead(char& symbol, int& count, bool& continue_mark)
int Dead(char& symbol, int& menu_mark)
{
    ClearScreen();

    std::string text = "YOU DIED";

    char c = '0';

    //PlayVideo();

    std::cout << "\n\n    ";
    SetConsoleTextAttribute(hConsole, 12); // 12 - Red
    FlashTextLong(text);
    std::cout << text;
    SetConsoleTextAttribute(hConsole, 7); // 7 - Default

    std::this_thread::sleep_for(std::chrono::seconds(1)); // 1s

    std::cout << "\n\n    ";
    std::cout << "Press any key to continune...";

    c = _getch();   // 'ESC' = 27

    menu_mark = 1;

    symbol = c;

    return 0;
}

void LoadingAnimation()
{
    //Sleep(50);
    std::this_thread::sleep_for(std::chrono::nanoseconds(10000000)); // 10.000.000
    std::cout << "." << std::flush;
    //Sleep(50);
    std::this_thread::sleep_for(std::chrono::nanoseconds(10000000)); // 10.000.000
    std::cout << "." << std::flush;
    //Sleep(50);
    std::this_thread::sleep_for(std::chrono::nanoseconds(10000000)); // 10.000.000
    std::cout << "." << std::flush;
    //Sleep(50);
    std::this_thread::sleep_for(std::chrono::nanoseconds(10000000)); // 10.000.000
    std::cout << "\b\b\b   \b\b\b" << std::flush;
}

int Loading(int for_i, int chapters_amount, int& n) // Need n = 0 before function starts
{
    int percent;

    percent = (for_i * 100) / chapters_amount;
    for (int k = n; k <= percent; k++)
    {
        std::cout << k << "%";
        if (k < 10)
        {
            std::cout << "\b\b";
        }
        else if (k < 100)
        {
            std::cout << "\b\b\b";
        }
        //Sleep(10);
        //std::this_thread::sleep_for(std::chrono::nanoseconds(10000)); // 10.000
        n = percent;
    }    

    return 0;
}