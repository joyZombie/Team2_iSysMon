#include "Timer.h"
#include "Incedo SysMonitor.h"

bool timerRunning = false;
UINT_PTR id;

void CALLBACK f(HWND hwnd, UINT uMsg, UINT timerId, DWORD dwTime)
{
    updateStats();
}


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

