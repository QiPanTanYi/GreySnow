#include <windows.h>
#include <stdio.h>
#include <string.h>
#include "display.h"

static HWND hWndOverlay;
static char recentKeys[5] = "    ";  // 最近的 4 个按键（第 5 位为空终止符）
static HFONT hFont;                 // 自定义字体

void InitDisplay(HINSTANCE hInstance) {
    WNDCLASS wc = {0};
    wc.lpfnWndProc = OverlayProc;
    wc.hInstance = hInstance;
    wc.lpszClassName = "KeyDisplayOverlay";

    RegisterClass(&wc);

    RECT screenRect;
    GetClientRect(GetDesktopWindow(), &screenRect);

    int width = 250, height = 150;  // 增大宽高，适配大字母
    int x = screenRect.right - width -  10;
    int y = screenRect.bottom - height - 40;

    hWndOverlay = CreateWindowEx(
            WS_EX_TOPMOST | WS_EX_LAYERED | WS_EX_NOACTIVATE,
            "KeyDisplayOverlay", NULL, WS_POPUP,
            x, y, width, height, NULL, NULL, hInstance, NULL
    );

    // 设置白底透明
    SetLayeredWindowAttributes(hWndOverlay, 0, 130, LWA_ALPHA);

    // 创建自定义字体（大号，粗体）
    hFont = CreateFont(
            49, 0, 0, 0, FW_BOLD, FALSE, FALSE, FALSE, ANSI_CHARSET,
            OUT_TT_PRECIS, CLIP_DEFAULT_PRECIS, DEFAULT_QUALITY, DEFAULT_PITCH, "Arial"
    );

    ShowWindow(hWndOverlay, SW_SHOW);
}

void UpdateKeyDisplay(char key) {
    // 滚动队列逻辑
    memmove(recentKeys, recentKeys + 1, 3);
    recentKeys[3] = key;  // 插入最新按键
    InvalidateRect(hWndOverlay, NULL, TRUE);  // 请求重绘
}

LRESULT CALLBACK OverlayProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam) {
    if (message == WM_PAINT) {
        PAINTSTRUCT ps;
        HDC hdc = BeginPaint(hWnd, &ps);

        // 填充白底
        HBRUSH hBrush = CreateSolidBrush(RGB(0, 0, 0));  // 灰色画刷
        FillRect(hdc, &ps.rcPaint, hBrush);
        DeleteObject(hBrush);

        // 设置字体
        SelectObject(hdc, hFont);
        SetTextColor(hdc, RGB(0, 200, 0));  // 深绿色字体
        SetBkMode(hdc, TRANSPARENT);     // 字体背景透明

        // 格式化输出：用空格分隔字母
        char displayText[20];
        snprintf(displayText, sizeof(displayText), "%c   %c   %c   %c",
                 recentKeys[0], recentKeys[1], recentKeys[2], recentKeys[3]);

        TextOut(hdc, 10, 40, displayText, strlen(displayText));  // 显示大号字幕

        EndPaint(hWnd, &ps);
        return 0;
    }
    return DefWindowProc(hWnd, message, wParam, lParam);
}

void CleanupDisplay() {
    if (hFont) {
        DeleteObject(hFont);  // 释放字体资源
    }
}