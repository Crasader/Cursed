#ifndef __SHIELD_MANAGER_H__
#define __SHIELD_MANAGER_H__

#include "Default.h"

#define ShieldMotionNum 20

enum ShieldMottion {
	ShieldWalk, ShieldJump, ShieldLadder, ShieldDash, ShieldAttack, ShieldHit, ShieldDeath,
	ShieldStand
};

class ShieldManager
{
public:
	Animation *effect[ShieldMotionNum];
	void AnimationInit();
	Sprite* m_Shield[3];// ����, ����, ����
	int m_Hard[3];// �� HP

	int m_MotionNum;
	Layer* m_layer;

	void GetLayer(Layer* layer);
	void CreateMotion();
	void SettingShield(int tagNum);
	void MotionSwitch(int num);
	void FollowHero();
};

#endif 