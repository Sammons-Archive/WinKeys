#include "WindowGroup.h"

#pragma once

class HotkeyManager
{
private:
	WindowGroup windowGroups[10];
	bool enableHotkeys;
protected:
	void RegisterNumericHotkeys();
	void ClearWindows();
	void AssignWindow(WPARAM msgId);
	void ToggleWindowGroup(WPARAM msgId);
	void ToggleHotkeysEnabled();
public:
	HotkeyManager();
	~HotkeyManager();
	void RegisterHotKeys();
	void ProcessHotkeyMessage(MSG msg);
};

