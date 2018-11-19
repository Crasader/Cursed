#include "Default.h"

Timer2* m_Timer2 = new Timer2;

Timer2::Timer2()
{
	m_curTime = 0;
}

void Timer2::SetTime(float dt)
{
	m_curTime += dt;
}

float Timer2::GetTime()
{
	return m_curTime;
}

