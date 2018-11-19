#ifndef __TIMER2_H__
#define __TIMER2_H__

#include "cocos2d.h"
#include "Default.h"

USING_NS_CC;


class Timer2
{
public:
	Timer2();
	float m_curTime;
	void SetTime(float dt);
	float GetTime();

};

#endif 