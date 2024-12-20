// statusbar.c
#include "statusbar.h"
#include <windows.h>
#include <wchar.h>

void DrawStatusBar(HDC hdc, BOOL capsLock, BOOL isChineseInput, int width, int height) {
    const int statusBarHeight = 20;
    RECT rect = {0, height - statusBarHeight, width, height};

    // 绘制状态栏背景
    HBRUSH hBrush = CreateSolidBrush(RGB(255, 255, 255)); // 白色背景
    FillRect(hdc, &rect, hBrush);
    DeleteObject(hBrush);

    // 绘制状态栏文本
    HFONT hFont = (HFONT)GetStockObject(SYSTEM_FONT);
    SelectObject(hdc, hFont);
    SetTextColor(hdc, RGB(0, 0, 0)); // 黑色字体
    SetBkMode(hdc, TRANSPARENT); // 透明背景

    wchar_t statusText[256];
    swprintf(statusText, L"%s    %s    设置",
             capsLock ? L"大写" : L"小写",
             isChineseInput ? L"中文" : L"英文");

    DrawText(hdc, statusText, -1, &rect, DT_LEFT | DT_SINGLELINE | DT_VCENTER);
}