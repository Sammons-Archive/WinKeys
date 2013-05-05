#include "stdafx.h"
#include "WindowGroup.h"

WindowGroup::WindowGroup()
{
}

WindowGroup::~WindowGroup()
{
}

void WindowGroup::ShowAllWindows()
{
	wprintf(L"Showing All Windows\n");
	SendMessageAllWindows(WM_SYSCOMMAND, SC_RESTORE, NULL);
}

void WindowGroup::HideAllWindows()
{
	wprintf(L"Hiding All Windows\n");
	SendMessageAllWindows(WM_SYSCOMMAND, SC_MINIMIZE, NULL);
}

void WindowGroup::SendMessageAllWindows(UINT msg, WPARAM wp, LPARAM lp)
{
	for(auto &win : windowHandles)
	{
		SendMessage(win, msg, wp, lp);
	}
}

void WindowGroup::AddWindow(HWND hwnd)
{
	wprintf(L"Adding Window: %d\n");
	windowHandles.push_back(hwnd);
}

void WindowGroup::ClearWindows()
{
	windowHandles.clear();
}

bool WindowGroup::ToggleWindows()
{
	if(activated)
		HideAllWindows();
	else
		ShowAllWindows();

	activated = !activated;
	return activated;
}