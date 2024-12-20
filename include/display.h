// display.h
#ifndef DISPLAY_H
#define DISPLAY_H

#include <windows.h>

void InitDisplay(HINSTANCE hInstance);
void UpdateKeyDisplay(char key);
LRESULT CALLBACK OverlayProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);
void CleanupDisplay();

#endif // DISPLAY_H