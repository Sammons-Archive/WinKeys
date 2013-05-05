#include "stdafx.h"
#include "HotkeyManager.h"

#define TOGGLE_HKID_START 0
#define TOGGLE_HKID_END 9
#define ADD_HKID_START 10
#define ADD_HKID_END 19
#define TOGGLE_ALL_KEY 'Q'
#define CLEAR_ALL_KEY 'Z'
#define TOGGLE_ALL_HKID 21
#define CLEAR_ALL_HKID 22

HotkeyManager::HotkeyManager()
{
}


HotkeyManager::~HotkeyManager()
{
}

void HotkeyManager::RegisterHotKeys()
{
	RegisterHotKey(NULL, TOGGLE_ALL_HKID, MOD_ALT | MOD_SHIFT | MOD_NOREPEAT, TOGGLE_ALL_KEY);
	RegisterHotKey(NULL, CLEAR_ALL_HKID, MOD_ALT | MOD_SHIFT | MOD_NOREPEAT, CLEAR_ALL_KEY);
	RegisterNumericHotkeys();
}

void HotkeyManager::AssignWindow(WPARAM msgId)
{
	wprintf(L"Adding Window to key: %c\n", msgId + '0' - ADD_HKID_START);
	windowGroups[msgId - ADD_HKID_START].AddWindow(GetForegroundWindow());
}

void HotkeyManager::ClearWindows()
{
	wprintf(L"Clearing All Hotkeys\n");
	for(auto &wg : windowGroups)
	wg.ClearWindows();
}
void HotkeyManager::ToggleWindowGroup(WPARAM msgId)
{

	auto state = windowGroups[msgId - TOGGLE_HKID_START].ToggleWindows();
	wprintf(L"Toggling Key: %c to state: %d\n", msgId + '0', state);
}
void HotkeyManager::ToggleHotkeysEnabled()
{
	wprintf(L"Toggling Hotkeys to %d\n",!enableHotkeys);
	enableHotkeys = !enableHotkeys;
}

void HotkeyManager::ProcessHotkeyMessage(MSG msg)
{
	if (msg.wParam == TOGGLE_ALL_HKID)//first must check for hotkey to turn off/on all others
		ToggleHotkeysEnabled();
	else if(msg.wParam == CLEAR_ALL_HKID)
		ClearWindows();
	else if(enableHotkeys && msg.wParam >= ADD_HKID_START && msg.wParam <= ADD_HKID_END)
		AssignWindow(msg.wParam);
	else if(enableHotkeys && msg.wParam >= TOGGLE_HKID_START && msg.wParam <= TOGGLE_HKID_END)
		ToggleWindowGroup(msg.wParam);
}

void HotkeyManager::RegisterNumericHotkeys()
{
	for (char c = '0'; c <= '9'; c++)
	{
		wprintf(L"Registering 0x%x\n", c);
		RegisterHotKey(NULL, c - '0' + ADD_HKID_START, MOD_ALT | MOD_SHIFT | MOD_NOREPEAT, c);
		RegisterHotKey(NULL, c - '0' + TOGGLE_HKID_START, MOD_ALT | MOD_NOREPEAT, c);
	}
}