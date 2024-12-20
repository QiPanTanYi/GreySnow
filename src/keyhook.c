#include <windows.h>
#include "keyhook.h"
#include "display.h"

static HHOOK hKeyboardHook;

LRESULT CALLBACK KeyboardProc(int nCode, WPARAM wParam, LPARAM lParam) {
    if (nCode >= 0 && wParam == WM_KEYDOWN) {
        KBDLLHOOKSTRUCT *pKeyStruct = (KBDLLHOOKSTRUCT *)lParam;
        char key = MapVirtualKey(pKeyStruct->vkCode, MAPVK_VK_TO_CHAR);

        // 只处理可打印字符并区分大小写
        if (key >= 32 && key <= 126) {
            UpdateKeyDisplay(key);
        }
    }
    return CallNextHookEx(hKeyboardHook, nCode, wParam, lParam);
}

void SetKeyboardHook() {
    hKeyboardHook = SetWindowsHookEx(WH_KEYBOARD_LL, KeyboardProc, GetModuleHandle(NULL), 0);
}

void RemoveKeyboardHook() {
    UnhookWindowsHookEx(hKeyboardHook);
}
