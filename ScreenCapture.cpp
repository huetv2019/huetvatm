#include <windows.h>
#include <gdiplus.h>
#include <string>

using namespace Gdiplus;
#pragma comment (lib, "Gdiplus.lib")

extern "C" __declspec(dllexport) int CaptureScreen(const char* filePath) {
    ULONG_PTR gdiplusToken;
    GdiplusStartupInput gdiPlusStartupInput;
    GdiplusStartup(&gdiplusToken, &gdiPlusStartupInput, NULL);

    HDC hScreen = GetDC(NULL);
    HDC hDC = CreateCompatibleDC(hScreen);
    int width = GetSystemMetrics(SM_CXSCREEN);
    int height = GetSystemMetrics(SM_CYSCREEN);
    
    HBITMAP hBitmap = CreateCompatibleBitmap(hScreen, width, height);
    SelectObject(hDC, hBitmap);
    BitBlt(hDC, 0, 0, width, height, hScreen, 0, 0, SRCCOPY);
    
    Bitmap bitmap(hBitmap, NULL);
    CLSID clsid;
    CLSIDFromString(L"{557CF406-1A04-11D3-9A73-0000F81EF32E}", &clsid);
    wchar_t wFilePath[MAX_PATH];
    MultiByteToWideChar(CP_ACP, 0, filePath, -1, wFilePath, MAX_PATH);
    bitmap.Save(wFilePath, &clsid, NULL);

    DeleteObject(hBitmap);
    DeleteDC(hDC);
    ReleaseDC(NULL, hScreen);
    GdiplusShutdown(gdiplusToken);
    
    return 0;
}
