// WinKeys.cpp : Defines the entry point for the console application.
//


#include "stdafx.h"
#include <Windows.h>
#include <vector>
using std::vector;
/*
To use, begin the application,
alt+shift+q will activate/deactivate hotkeys
alt+shift+z will erase all hotkeys
alt+shift+num will assign the current window to the group number pressed
alt+num will toggle minimize/restore of windows in that num group

cheers, Ben Sammons (with much help from David Logsdon)
*/
int _tmain(int argc, _TCHAR* argv[])
{
	int i,j;
	bool activatedMe = false;
	bool activatedGroup[10] = {0};
	vector<HWND>* allVectors[10];
	for (i=0;i<10;i++)
	{
		allVectors[i] = new vector<HWND>();
	}


	RegisterHotKey(NULL,21,MOD_ALT | MOD_SHIFT | MOD_NOREPEAT,0x51);//q
	RegisterHotKey(NULL,22,MOD_ALT | MOD_SHIFT | MOD_NOREPEAT,0x5A);//q
	RegisterHotKey(NULL,11,MOD_ALT | MOD_SHIFT | MOD_NOREPEAT,0x30);//0-9
	RegisterHotKey(NULL,12,MOD_ALT | MOD_SHIFT | MOD_NOREPEAT,0x31);
	RegisterHotKey(NULL,13,MOD_ALT | MOD_SHIFT | MOD_NOREPEAT,0x32);
	RegisterHotKey(NULL,14,MOD_ALT | MOD_SHIFT | MOD_NOREPEAT,0x33);
	RegisterHotKey(NULL,15,MOD_ALT | MOD_SHIFT | MOD_NOREPEAT,0x34);
	RegisterHotKey(NULL,16,MOD_ALT | MOD_SHIFT | MOD_NOREPEAT,0x35);
	RegisterHotKey(NULL,17,MOD_ALT | MOD_SHIFT | MOD_NOREPEAT,0x36);
	RegisterHotKey(NULL,18,MOD_ALT | MOD_SHIFT | MOD_NOREPEAT,0x37);
	RegisterHotKey(NULL,19,MOD_ALT | MOD_SHIFT | MOD_NOREPEAT,0x38);
	RegisterHotKey(NULL,20,MOD_ALT | MOD_SHIFT | MOD_NOREPEAT,0x39);
	RegisterHotKey(NULL,0,MOD_ALT | MOD_NOREPEAT,0x30);//0-9
	RegisterHotKey(NULL,1,MOD_ALT | MOD_NOREPEAT,0x31);
	RegisterHotKey(NULL,2,MOD_ALT | MOD_NOREPEAT,0x32);
	RegisterHotKey(NULL,3,MOD_ALT | MOD_NOREPEAT,0x33);
	RegisterHotKey(NULL,4,MOD_ALT | MOD_NOREPEAT,0x34);
	RegisterHotKey(NULL,5,MOD_ALT | MOD_NOREPEAT,0x35);
	RegisterHotKey(NULL,6,MOD_ALT | MOD_NOREPEAT,0x36);
	RegisterHotKey(NULL,7,MOD_ALT | MOD_NOREPEAT,0x37);
	RegisterHotKey(NULL,8,MOD_ALT | MOD_NOREPEAT,0x38);
	RegisterHotKey(NULL,9,MOD_ALT | MOD_NOREPEAT,0x39);

 
    MSG msg = {0};
    while (GetMessage(&msg, NULL, 0, 0) != 0)
    {
		if (activatedMe)
		{
			for (i=0;i<10;i++) {
				if (msg.wParam == i) {//if ctrl + i where i 0 to 9 then toggle windows in group

					printf("WM_HOTKEY received %d\n",msg.wParam);
					if (activatedGroup[i])
					{// if this group is activated already, minimize and deactivate
						j = allVectors[i]->size()-1;
						while (j!=-1) {//iterating through the handles in the group
							if (activatedGroup[i]){
								SendMessage(allVectors[i]->at(j), WM_SYSCOMMAND, SC_MINIMIZE, NULL);
							j--;
							}
						}
					} else {// if this group is minimized, restore and activate
						j = allVectors[i]->size()-1;
						while (j!=-1) {//iterating through the handles in the group
							if (!activatedGroup[i]){
								SendMessage(allVectors[i]->at(j), WM_SYSCOMMAND, SC_RESTORE, NULL);
							j--;
							} 
						}
					}
					activatedGroup[i] = !activatedGroup[i];
				}
			}
			for (i=11;i<20;i++) {
				if (msg.wParam == i) {//if ctrl + shift + i where i 0 to 9 then add current window to group i
					printf("WM_HOTKEY received %d\n",msg.wParam);
					auto windowOfInterest = GetForegroundWindow();
					allVectors[i-11]->push_back(windowOfInterest);
				}
			}

			if (msg.wParam == 21){
				printf("WM_HOTKEY received %d\n",msg.wParam);
				activatedMe = false;
			} 
		} else {
			if (msg.wParam == 21){
				printf("WM_HOTKEY received %d\n",msg.wParam);
				activatedMe = true;
			}
		}
			if (msg.wParam == 22){//reset all mappings
					for (i=0;i<10;i++)
					{
					allVectors[i] = new vector<HWND>();
					}
			}
	} 
	return 0;
} 

