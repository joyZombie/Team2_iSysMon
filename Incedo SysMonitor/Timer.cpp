#include "Timer.h"
#include "Incedo SysMonitor.h"

bool timerRunning = false;
UINT_PTR id;

void CALLBACK f(HWND hwnd, UINT uMsg, UINT timerId, DWORD dwTime)
{
    updateStats();
}

//UINT_PTR Timer::timerId = 0L;
//map<UINT_PTR, Timer*> Timer::mp = map<UINT_PTR, Timer*>();


void startTimer(UINT time)
{
    if (timerRunning) return;
    id = SetTimer(NULL, 555, 1000 * time, (TIMERPROC)&f);
    timerRunning = true;
}

void stopTimer()
{
    if (!timerRunning) return;
    KillTimer(NULL, id);
    timerRunning = false;
}

//Timer::Timer(int time, void (* func)())
//{
//    timerId++;
//    auto id = SetTimer(NULL, timerId, 1000 * time, (TIMERPROC)&Timer::f);
//    currId = id;
//    mp[id] = this; 
//}
//
//void Timer::callFunction()
//{
//    (* func)();
//}
//
//void Timer::stopTimer()
//{
//
//}
//
//void CALLBACK Timer::f(HWND hwnd, UINT uMsg, UINT timerId, DWORD dwTime)
//{
//    mp[timerId]->callFunction();
//}
//
//Timer::~Timer()
//{
//    mp.erase(currId);
//}
