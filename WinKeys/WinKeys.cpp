// WinKeys.cpp : Defines the entry point for the console application.
//


#include "stdafx.h"
#include "HotkeyManager.h"
using std::vector;
/*
To use, begin the application,
alt+shift+q will activate/deactivate hotkeys
alt+shift+z will erase all hotkeys
alt+shift+num will assign the current window to the group number pressed
alt+num will toggle minimize/restore of windows in that num group

cheers, Ben Sammons (with much help from David Logsdon)
*/

HotkeyManager hotkeyManager;

int _tmain(int argc, _TCHAR* argv[])
{
	ShowWindow( GetConsoleWindow(), SW_HIDE );
	hotkeyManager.RegisterHotKeys();

	MSG msg;
	while (GetMessage(&msg, NULL, 0, 0) != 0)
	{
		if(msg.message == WM_HOTKEY) hotkeyManager.ProcessHotkeyMessage(msg);
	}

	return 0;
} 

