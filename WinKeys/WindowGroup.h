#pragma once


class WindowGroup
{	
private:
	std::vector<HWND> windowHandles;
	bool activated;
protected:
	void ShowAllWindows();
	void HideAllWindows();
	void SendMessageAllWindows(UINT msg, WPARAM wp, LPARAM lp);
public:	
	WindowGroup();
	~WindowGroup();
	void AddWindow(HWND hwnd);
	void ClearWindows();
	bool ToggleWindows();
};

