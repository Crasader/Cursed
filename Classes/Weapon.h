#ifndef __WEAPON_H__
#define __WEAPON_H__

#include "Default.h"

#define WeaponAniNum 10
//enum WeaponEff {
//	CloseStand, CloseWalk, CloseLadder, CloseJump, CloseHit, // 1
//	LongStand, LongWalk, LongLadder, LongJump, LongHit // 2
//};
class Weapon
{
public:

	Sprite* m_Spr;
	Sprite* ForChange;

	Animation *m_Effect[WeaponAniNum];
	int m_Att[10];

	void FollowHero();
	void WeaponRun();
	void SetWeapon(int tag);
	void AnimationSwitch(int num);
	void AniInit(int tag);
};

#endif 