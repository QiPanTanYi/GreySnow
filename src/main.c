// main.c
#include <windows.h>
#include "keyhook.h"
#include "display.h"

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow) {
    InitDisplay(hInstance);
    SetKeyboardHook();

    MSG msg;
    while (GetMessage(&msg, NULL, 0, 0)) {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }

    RemoveKeyboardHook();
    CleanupDisplay();
    return 0;
}