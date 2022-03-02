#include "SystemInformation.h"
#include <Windows.h>
#include <stdio.h>
#include <map>


#pragma once

void startTimer(UINT time);
void stopTimer();

//class Timer
//{
//private:
//	void (*func)();
//	UINT_PTR currId;
//	
//public:
//	static UINT_PTR timerId;
//	static map<UINT_PTR, Timer*> mp;
//	static void CALLBACK f(HWND hwnd, UINT uMsg, UINT timerId, DWORD dwTime);
//	Timer(int time, void (*func)());
//	~Timer();
//	void callFunction();
//	void stopTimer();
//};