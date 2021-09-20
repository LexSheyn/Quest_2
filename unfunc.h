#pragma once
#include <iostream>
#include <fstream>
#include <cstring>
#include <string>
#include <windows.h>
#include <cstdio>
#include <cstdlib>
#include <vector>
#include <conio.h>
#include <ctime>

#include "func.h"

using namespace std;

void writedel(string text, int speed, int delay)
{
    string t = text;
    int s = speed;       // Milliseconds
    int del = delay;        // Milliseconds
    int len = t.length();

    for (int i = 0; i < t.length(); i++)
    {
        Sleep(s);

        cout << t[i];
    }

    Sleep(del);

    cout << string(t.length(), '\b');

    for (int i = 0; i < t.length(); i++)
    {
        for (int i = 0; i < len; i++)
        {
            cout << t[i];
        }
        Sleep(15);
        cout << string(len, '\b');
        cout << string(len, ' ');
        cout << string(len, '\b');
        len--;
    }
}

int randomize(int& number)
{    
    int r = (rand() % 18) + 1;

    switch (r)
    {
    case 1:
        r = (int)'!';
        break;
    case 2:
        r = (int)'@';
        break;
    case 3:
        r = (int)'#';
        break;
    case 4:
        r = (int)'$';
        break;
    case 5:
        r = (int)'%';
        break;
    case 6:
        r = (int)'^';
        break;
    case 7:
        r = (int)'&';
        break;
    case 8:
        r = (int)'*';
        break;
    case 9:
        r = (int)'1';
        break;
    case 10:
        r = (int)'2';
        break;
    case 11:
        r = (int)'3';
        break;
    case 12:
        r = (int)'4';
        break;
    case 13:
        r = (int)'5';
        break;
    case 14:
        r = (int)'6';
        break;
    case 15:
        r = (int)'7';
        break;
    case 16:
        r = (int)'8';
        break;
    case 17:
        r = (int)'9';
        break;
    case 18:
        r = (int)'0';
        break;
    }

    number = r;

    return 0;
}

void writeS(string text, int ms)
{
    string a = text;
    int time = ms;

    int n = 0;
    
    for (int i = 0; i < a.length(); i++)
    {        
        Sleep(time);

        if (a[i] != '\n')
        {
            cout << a[i];
            //cout << '$';
            randomize(n);
            cout << char(n);
            randomize(n);
            cout << char(n);
            randomize(n);
            cout << char(n);
            randomize(n);
            cout << char(n);
            randomize(n);
            cout << char(n);
            cout << "\b\b\b\b\b";
        }
        else
        {
            cout << "     ";
            cout << "\b\b\b\b\b";
            cout << a[i];
        }
    }    
    cout << "     ";
    cout << "\b\b\b\b\b";
    Sleep(1000000);
}