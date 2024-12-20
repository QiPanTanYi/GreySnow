// statusbar.h
#ifndef STATUSBAR_H
#define STATUSBAR_H

#include <windows.h>

void DrawStatusBar(HDC hdc, BOOL capsLock, BOOL isChineseInput, int width, int height);

#endif // STATUSBAR_H